import sys
from mesonbuild import mesonmain
from pathlib import Path
import subprocess
import shutil

SYSTEM_LIBS = {
    "libc.so", "libm.so", "libgcc_s.so", "libstdc++.so", 
    "libpthread.so", "libdl.so", "librt.so", "libutil.so",
    "libcrypt.so", "libresolv.so", "libnsl.so", "ld-linux.so",
    "libX11.so", "libGL.so", "libdrm.so", # Often better to use system's GPU drivers
    "libz.so"
}

def is_system_lib(lib_name):
    return any(lib_name.startswith(s) for s in SYSTEM_LIBS)

def compile_engine():
    print("Compiling engine with meson...")
    args = ['setup', 'build', '--reconfigure']
    mesonmain.run(args, 'meson')

    args = ['compile', '-C', 'build']
    if mesonmain.run(args, 'meson') != 0:
        exit(1)

def generate_sdk_dir():
    sdk_dir = sys.argv[1]

    Path(sdk_dir).mkdir(exist_ok=True)
    Path(f"{sdk_dir}/lib").mkdir(exist_ok=True)
    Path(f"{sdk_dir}/include").mkdir(exist_ok=True)

def get_engine_dependencies(engine_lib):
    print("Parsing dependencies...")

    result = subprocess.run(['ldd', engine_lib], capture_output=True, text=True)
    if result.returncode != 0:
        print(result.stderr)
        exit(0)

    deps = []
    
    for line in result.stdout.splitlines():
        if "=>" not in line:
            continue
            
        parts = line.split("=>")
        lib_name = parts[0].strip()
        lib_path_str = parts[1].split("(")[0].strip()
        
        if not lib_path_str or not lib_path_str.startswith("/"):
            continue
            
        lib_path = Path(lib_path_str)

        if is_system_lib(lib_name):
            print(f"Skipping system lib: {lib_name}")
            continue
        
        deps.append(lib_path)
    return deps

def copy_libs(engine_lib, deps):
    print("Copying libraries...")
    engine_path = Path(engine_lib)
    sdk_dir = sys.argv[1]
    lib_dir = Path(f"{sdk_dir}/lib")

    print(f"Copying: {engine_lib}")
    shutil.copy2(engine_path, lib_dir)

    for dep in deps:
        print(f"Copying: {dep}")
        shutil.copy2(dep, lib_dir)

def fix_lib_rpath(engine_path):
    print("Patching engine RPATH...")
    try:
        # We use $ORIGIN (literally) in the command.
        subprocess.run([
            "patchelf", 
            "--set-rpath", "$ORIGIN", 
            str(engine_path)
        ], check=True)
    except subprocess.CalledProcessError as e:
        print(f"Failed to patch {engine_path}: {e}")
        exit(0)
    except FileNotFoundError:
        print("patchelf is not installed!")
        exit(0)

def copy_headers():
    print("Copying headers...")
    sdk_dir = sys.argv[1]
    src_dir = Path("src")
    include_dir = Path(sdk_dir + "/include")

    for file in src_dir.rglob("*"):
        if file.is_file() and file.name.endswith("hpp"):
            rel_path = file.relative_to(src_dir)
            target_dir = include_dir / rel_path.parent
            target_dir.mkdir(parents=True, exist_ok=True)
            print(f"Copying: {rel_path}")
            shutil.copy2(file, target_dir)
    
    flecs_include = Path("subprojects/flecs/include/")
    print("Copying flecs...")
    shutil.copytree(flecs_include, Path(sdk_dir + "/include"), dirs_exist_ok=True)

def copy_meson_config():
    print("Copying SDK meson config...")
    sdk_dir = sys.argv[1]
    meson_config = Path("sdk.build")
    output_config = Path(sdk_dir + "/meson.build")

    shutil.copy2(meson_config, output_config)

def generate_master_header():
    print("Generating master header...")
    src_dir = Path("src")
    sdk_dir = sys.argv[1]
    include_dir = sdk_dir + "/include"

    lines = [
        "#ifndef SINGULARITY_HPP",
        "#define SINGULARITY_HPP",
        ""
    ]

    for file in src_dir.rglob("*"):
        if file.is_file() and file.name.endswith("hpp"):
            lines.append(f"#include <{file.relative_to(src_dir)}>")

    lines.append("")
    lines.append("#endif // SINGULARITY_HPP")

    open(include_dir + "/singularity.hpp", "w").write("\n".join(lines))

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print(f"usage: {sys.argv[0]} <SDK output directory>")
        exit(1)
    
    sdk_dir = sys.argv[1]

    compile_engine()
    generate_sdk_dir()
    deps = get_engine_dependencies('build/libsingularity.so')
    copy_libs('build/libsingularity.so', deps)
    fix_lib_rpath(sdk_dir + "/lib/libsingularity.so")
    copy_headers()
    generate_master_header()
    copy_meson_config()
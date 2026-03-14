use png::Decoder;
use crate::types::image::Image;
use std::io::BufReader;
use std::fs::File;

pub fn load_png(filename: &str) -> Result<Image, ()> {
    let data = File::open(filename).map_err(|_| ())?;
    let decoder = Decoder::new(BufReader::new(data));
    let mut reader = decoder.read_info().map_err(|_| ())?;

    let size = match reader.output_buffer_size() {
        Some(size) => size,
        None => return Err(()),
    };

    let mut buffer = vec![0; size];
    let info = reader.next_frame(&mut buffer).map_err(|_| ())?;
    let bytes = &buffer[..info.buffer_size()];

    Ok(Image {
        width: info.width,
        height: info.height,
        data: bytes.to_vec(),
    })
}
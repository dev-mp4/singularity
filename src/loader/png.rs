use spng::{Decoder, Format};
use crate::types::image::Image;
use std::fs::{read, File};

pub fn load_png(filename: &str) -> Result<Image, ()> {
    let file = File::open(filename).map_err(|_| ())?;
    let mut decoder = Decoder::new(file);
    decoder.set_output_format(Format::Rgba8);
    let (out_info, mut reader) = decoder.read_info().map_err(|_| ())?;
    let size = reader.output_buffer_size();

    let mut out = vec![0; size];
    reader.next_frame(&mut out).map_err(|_| ())?;

    Ok(Image{
        width: reader.info().width,
        height: reader.info().height,
        data: out,
    })
}
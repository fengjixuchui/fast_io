use std::fs::File;
use std::io::BufWriter;

fn main()
{
	let f = File::create("rust.txt").unwrap();
	let mut f = BufWriter::with_capacity(1048576,f);
	for i in 0..10000000
	{
		itoa::write(&mut f,i).unwrap();
	}
}
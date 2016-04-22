function convert_pgm2jpg(filename)
input_image = imread(filename, 'pgm');
new_filename = [filename(1:length(filename)-4) '.jpg'];
imwrite(input_image, new_filename);

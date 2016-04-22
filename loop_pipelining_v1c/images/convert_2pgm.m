function convert_2pgm(input_filename)
input_filename_extension = input_filename(length(input_filename)-2:length(input_filename));
input_image_color = imread(input_filename, input_filename_extension);
[n_rows, n_cols, n_bands] = size(input_image_color);
if (n_bands > 1)
    input_image = uint8(mean(input_image_color, 3));
else
    input_image = uint8(input_image_color);
end;
output_filename = [input_filename(1:length(input_filename)-4) '.pgm'];
fid_write_prog = fopen(output_filename,'w');

fprintf(fid_write_prog,'P2\n');
fprintf(fid_write_prog,'%d %d\n', n_cols, n_rows);
fprintf(fid_write_prog,'255\n');

for i = 1: n_rows
    for j = 1: n_cols
        fprintf(fid_write_prog,'%d ', input_image(i,j));
    end;
    fprintf(fid_write_prog,'\n');
end;

fclose(fid_write_prog);

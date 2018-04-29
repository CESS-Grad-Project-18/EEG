arduino = serial('COM3', 'BaudRate', 9600);
%set(arduino, 'DataBits', 8);
%set(arduino, 'StopBits', 1);
%set(arduino, 'Parity', 'none');
fopen(arduino);
t1 = linspace(1, 100);
for i=1:length(t1)
    %t2(i) = fscanf(arduino, '%d');
    disp(fscanf(arduino, '%s'))
end
fprintf(arduino, char(3));
fclose(arduino);
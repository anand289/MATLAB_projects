clear;
[file_names,location] = uigetfile('*','Select a file','MultiSelect','on');

if class(file_names) == "char" % case 1: Only 1 file selected --> if only one file is selected, length(flie_names) = length of characters in the name
    str = file_names;
    new_str = replaceBetween(str,'.',str(end),'.value','Boundaries','inclusive');
else                          % case 2: Multiple files selected --> if multiple file names are selected, length(flie_names) = number of files in the cell array
    for i = 1:length(file_names)
        str = file_names(1,i);
        str = char(str);\
        % to replace substring after '.' with string 'value'
        new_str{1,i} = replaceBetween(str,'.',str(end),'.value','Boundaries','inclusive'); 
    end
end

Foldername = uigetdir('\'); 
folder = [Foldername,'/'];

if class(file_names) == "char"
    copyfile(strcat(location,file_names),strcat(folder,new_str))
else
    for i = 1:length(file_names)
        % to copy file from a certain folder and copy it in new location
        % with desired name
        copyfile(strcat(location,file_names{1,i}),strcat(folder,new_str{1,i}))
    end
end
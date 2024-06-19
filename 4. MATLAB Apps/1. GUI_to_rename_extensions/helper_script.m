clear;
[file_names,location] = uigetfile('*','Select a file','MultiSelect','on');

if class(file_names) == "char" % case 1: Only 1 file selected
    str = file_names;
    new_str = replaceBetween(str,'.',str(end),'.value','Boundaries','inclusive');
else                          % case 2: Multiple files selected
    for i = 1:length(file_names)
        str = file_names(1,i);
        str = char(str);
        new_str{1,i} = replaceBetween(str,'.',str(end),'.value','Boundaries','inclusive');
    end
end

Foldername = uigetdir('\'); 
folder = [Foldername,'/'];

if class(file_names) == "char"
    copyfile(strcat(location,file_names),strcat(folder,new_str))
else
    for i = 1:length(file_names)
        copyfile(strcat(location,file_names{1,i}),strcat(folder,new_str{1,i}))
    end
end
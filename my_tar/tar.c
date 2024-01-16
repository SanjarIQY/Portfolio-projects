#include <grp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <pwd.h>

typedef struct posix_header
{                               /* byte offset */
  char name[100];               /*   0 */
  char mode[8];                 /* 100 */
  char uid[8];                  /* 108 */
  char gid[8];                  /* 116 */
  char size[12];                /* 124 */
  char mtime[12];               /* 136 */
  char chksum[8];               /* 148 */
  char typeflag;                /* 156 */
  char linkname[100];           /* 157 */
  char magic[6];                /* 257 */
  char version[2];              /* 263 */
  char uname[32];               /* 265 */
  char gname[32];               /* 297 */
  char devmajor[8];             /* 329 */
  char devminor[8];             /* 337 */
  char prefix[155];             /* 345 */
  char additional[12];          /* 500 */
} file_data;

typedef struct listnode
{
    char* file_name;
    struct stat fs;
    struct listnode* next;
}list;
 
void fill_with_null(char* name, int size)
{
    int i = 0;
    while(i < size)
    {
        name[i] = '\0';
        i++;
    }
}

int my_strlen(char* string)
{
    int i = 0;
    while(string[i] != '\0')
        i++;
    return i;
}

void fill_header(file_data* head)
{
    fill_with_null(head->name,100);             /*   0 */
    fill_with_null(head->mode, 8);              /* 100 */
    fill_with_null(head->uid, 8);               /* 108 */
    fill_with_null(head->gid, 8);               /* 116 */
    fill_with_null(head->size, 12);             /* 124 */
    fill_with_null(head->mtime, 12);            /* 136 */
    fill_with_null(head->chksum, 8);            /* 148 */
    head->typeflag = 0;                         /* 156 */
    fill_with_null(head->linkname, 100);        /* 157 */
    fill_with_null(head->magic, 6);             /* 257 */
    fill_with_null(head->version, 2);           /* 263 */
    fill_with_null(head->uname, 32);            /* 265 */
    fill_with_null(head->gname, 32); ;          /* 297 */
    fill_with_null(head->devmajor, 8);          /* 329 */
    fill_with_null(head->devminor, 8);          /* 337 */
    fill_with_null(head->prefix, 155);          /* 345 */
    fill_with_null(head->additional, 12);       /* 500 */
}

char* reverse(char* string)
{
    int length = my_strlen(string);
    char* str = (char*)malloc(sizeof(char) * length);
    fill_with_null(str, length);
    int j = 0;
    for(int i = length - 1; i >= 0; i--)
    {
        str[j] = string[i];
        j++;
    }
    str[j] = '\0';
    return str;
}

char* dec_to_octal(int p1, int size)
{
    char* ret_val = (char*)malloc(size);
    fill_with_null(ret_val, size);
    int i = 0;
    while(p1 > 0)
    {
        ret_val[i++] = (p1 % 8) + 48;
        p1 /= 8;
    }
    while(i < size - 1)
    {
        ret_val[i] = '0';
        i++;
    }
    ret_val[i] = '\0';
    return reverse(ret_val);
}

void my_copy(char* dest, char* source)
{
    int i = 0;

    while(source[i] != '\0')
    {
        dest[i] = source[i];
        i++;
    }    
}

int summ(char* string)
{
    int counter = 0;
    for(int i = 0; string[i] != '\0'; i++)
    {
        counter += (int)string[i];
    }
    return counter;
}

char* dec_to_char(int num)
{
    char* str_num = (char*)malloc(sizeof(char) * (num / 10) + 2);
    fill_with_null(str_num, (num / 10) + 2);
    int i = 0;
    while(num != 0)
    {
        str_num[i] = num % 10 + 48;
        i++;
        num /= 10;
    }
    return reverse(str_num);
}

int define_checksum(file_data* posix)
{
    int counter = 256;
    counter += summ(posix->name);
    counter += summ(posix->gname);
    counter += summ(posix->uname);
    counter += summ(posix->gid);
    counter += summ(posix->mtime);
    counter += summ(posix->size);
    counter += summ(posix->uid);
    counter += summ(posix->mode);
    counter += summ(posix->magic);
    counter += 48;
    // counter += summ(posix->linkname);
    return counter;
}

void fill_with_data(file_data *posix_header, list* file)
{
    struct passwd* fd = getpwuid(file->fs.st_uid);
    struct group* gid = getgrgid(file->fs.st_uid);
    
    my_copy(posix_header->name, file->file_name);
    my_copy(posix_header->mode, dec_to_octal(file->fs.st_mode, 8));
    my_copy(posix_header->mtime, dec_to_octal(file->fs.st_mtim.tv_sec, 12));
    my_copy(posix_header->uid, dec_to_octal(file->fs.st_uid, 8));
    my_copy(posix_header->gid, dec_to_octal(file->fs.st_gid, 8));
    my_copy(posix_header->size, dec_to_octal(file->fs.st_size, 12));
    posix_header->typeflag = 0;
    my_copy(&posix_header->typeflag, "0");
    my_copy(posix_header->magic, "ustar  ");
    my_copy(posix_header->uname, fd->pw_name);
    my_copy(posix_header->gname, gid->gr_name);
    int check_summ = define_checksum(posix_header);
    my_copy(posix_header->chksum,dec_to_octal(check_summ, 7));
}

void get_content(list* p1, int fd_created_file)
{
    int length = p1->fs.st_size;
    int count = 0;
    while(length > 0)
    {
        length -= 512;
        count++;
    }

    char* str = (char*)malloc(sizeof(char) * (count * 512) + 1);
    fill_with_null(str, (count * 512) + 1);
    int fd = open(p1->file_name, O_RDONLY);
    read(fd, str, p1->fs.st_size);
    close(fd);
    write(fd_created_file, str , count * 512);
    free(str);
}

void add_last(list** p1, char* name)
{
    list* new = (list*)malloc(sizeof(list));
    new->file_name = (char*)malloc(sizeof(char) * my_strlen(name) + 1);
    my_copy(new->file_name, name);
    stat(name, &new->fs);
    new->next = NULL;

    if(*p1 == NULL){
        *p1 = new;
    }
    else {
        list* head = *p1;
        while(head->next != NULL) 
        {
            head = head->next;
        }
        head->next = new;
    }
}

int compare(char* p1, char* p2)
{
    for(int i = 0; p1[i] != '\0'; i++)
    {
        if(p1[i] != p2[i])
            return 1;
    }
    return 0;
} 

void no_such_file(char* file_name)
{
    write(2,"my_tar: ", 8);
    write(2, file_name, my_strlen(file_name));
    write(2, ": Cannot stat: No such file or directory\n", 41);   
}

int ts_option(int argc, char** argv, int flag)
{
    if(argc > 3)
    {
        return 0;
    }

    int i = 0;
    int fd = open(argv[2], O_RDONLY);
    file_data ts;
    while(read(fd, &ts, 512))
    {
        if((compare(ts.magic, "ustar  ") ) == 0 && ts.typeflag)
        { 
            if(my_strlen(ts.name) < 50)
            {
                i++;
                if(flag == 0)
                {
                    write(1, ts.name, my_strlen(ts.name));
                    write(1, "\n", 1);
                }
            }
            
        }
    }
    close(fd);
    return i;
    //printf("%d\n", i);
}

void work(list* files, int fd_created_file)
{
    file_data posix_header;
    fill_header(&posix_header);
    fill_with_data(&posix_header, files);
    write(fd_created_file, &posix_header, 512);
    get_content(files, fd_created_file);
}

void cf_option(int argc, char** argv)
{
    list* files = NULL;
    int flag = 0;
    if((open(argv[2], O_RDONLY) > 0))
    {
        unlink(argv[2]);
    } 
    int *fd = malloc(sizeof(int) * argc - 3);
    int k = 0;
    for(int i = 3; i < argc; i++)
    {
        if((fd[k++] = open(argv[i], O_RDONLY) > 0))
        {
            add_last(&files, argv[i]);
        }
        else 
        {
            flag++;
            no_such_file(argv[i]);
        }
    }

    if(flag > 0)
    {
        write(2, "tar: Exiting with failure status due to previous erors\n",55);
        return;
    }

    creat(argv[2], 000644);
    int fd_created_file = open(argv[2], O_WRONLY | O_APPEND);
    
    while(files != NULL)
    {
        work(files, fd_created_file);
        files = files->next;
    }
    int i = 0;
    
    while(i < argc - 3)
    {
        close(fd[i]);
        i++;
    }
    free(fd);
}



void rf_option(int argc, char** argv)
{
    list* files = NULL;
    int *fd = malloc(sizeof(int) * argc - 3);
    int ind = 0, flag = 0;
    for(int i = 3; i < argc; i++)
    {
        if((fd[ind++] = open(argv[i], O_RDONLY)) > 0){
            add_last(&files, argv[i]);
        }
        else {
            flag++;
            no_such_file(argv[i]);
        }
    }
    if(flag > 0)
    {
        write(2, "tar: Exiting with failure status due to previous erors\n",55);
        return;
    }
    if(open(argv[2], O_RDONLY) < 0)
        creat(argv[2], 000644);
    int fd_created_file = open(argv[2], O_WRONLY | O_APPEND);

    file_data posix_header;
    while(files)
    {
        fill_header(&posix_header);
        fill_with_data(&posix_header, files);
        // printf("%s \n", posix_header.name);
        write(fd_created_file, &posix_header, 512);
        get_content(files, fd_created_file);
        files = files->next;
    }
    int i = 0;
    while(i < argc - 3) 
    {
        close(fd[i]);
        i++;
    }
    free(fd);
}

int counter(char* file)
{
    int fd = open(file, O_RDONLY);
    file_data ts;
    int counter = 0;
    while(read(fd, &ts, 512))
    {
        if((compare(ts.magic, "ustar  ") ) == 0 && ts.typeflag)
        { 
            if(my_strlen(ts.name) < 50)
            {
                counter++;
            }   
        }
    }
    return counter;
    close(fd);
}

int check_file(char** input, char* file_name)
{
    for(int i = 0; input[i]; i++)
    {
        if(compare(file_name, input[i]) == 0)
            return 1;
    }
    return 0;
}

int octalToDecimal(int n)
{
	int num = n;
	int dec_value = 0;
	int base = 1;

	int temp = num;
	while (temp) {
		int last_digit = temp % 10;
		temp = temp / 10;
		dec_value += last_digit * base;

		base = base * 8;
	}

	return dec_value;
}

char* my_strnncpy(char* destination, const char* source, int num)
{
    int i = 0;
    while(i < num)
    {
        destination[i] = source[i];
        i++;
    } 
    destination[i] = '\0';
    return destination;
}

char* content(file_data* xf, int fd)
{
    int size = atoi(xf->size);
    size = octalToDecimal(size);
    int len = size;

    int count = 0;
    while(len > 0)
    {
        len -= 512;
        count++;
    }

    char* string = malloc(sizeof(char) * (512 * count));
    fill_with_null(string, 512 * count);
    read(fd, string, (512 * count));
    char* temp = malloc(sizeof(char) * size + 1);

    fill_with_null(temp, size + 1);
    my_strnncpy(temp, string , size);
    return temp;
}

void tar_file_only(int argc, char** argv)
{
    int size = ts_option(argc , argv, 1);
    char** string = (char**)malloc(sizeof(char*) * size);
    file_data xf;
    int ind = 0;
    int fd = open(argv[2], O_RDONLY);
    while(read(fd, &xf, 512))
    {
        if((compare(xf.magic, "ustar  ") == 0) && xf.typeflag)
        {
            if(my_strlen(xf.name) < 100)
            {
                string[ind] = malloc(sizeof(char) * my_strlen(xf.name) + 1);
                fill_with_null(string[ind], my_strlen(xf.name) + 1);
                my_copy(string[ind], xf.name);
                ind++;
            }
            
        }
    }
    int* fd_arr = malloc(sizeof(int) * size);
    ind = 0;
    for(int i = 0; string[i]; i++)
    {
        if((fd_arr[ind] = open(string[i], O_RDONLY)) > 0)
            unlink(string[i]);
    }
    close(fd);

    int l = 0;
    char* cont;
    file_data xs;
    int fd1 = open(argv[2], O_RDONLY);
    while(read(fd1, &xs, 512))
    {
        if((compare(xs.magic, "ustar  ")) == 0 && check_file(string, xs.name) == 1)
        {    
            creat(xs.name, 000644);
            int size = atoi(xs.size);
            size = octalToDecimal(size);
            cont = malloc(sizeof(char) * size);
            fill_with_null(cont, size);
            my_copy(cont, content(&xs, fd1));
            fd_arr[l] = open(xs.name, O_WRONLY | O_APPEND);
            write(fd_arr[l], cont, size);
            l++; 
            free(cont);
        }
    }
    free(string);
    for(int i = 0; i < size; i++)
        close(fd_arr[i]);
    free(fd_arr);
}

void xf_option(int argc, char** argv)
{
    if(argc == 3)
    {
        tar_file_only(argc, argv);
        return;
    }
        
    char** array = malloc(sizeof(char*) * (argc - 3));
    int ind = 0; 
    int *fd = malloc(sizeof(int) * (argc - 3));
    for(int i = 3; i < argc; i++)
    {
        if((fd[ind] = open(argv[i], O_RDONLY)) > 0)
        {
            unlink(argv[i]);
        }
        array[ind] = malloc(sizeof(char) * (my_strlen(argv[i]) + 1));
        fill_with_null(array[ind], my_strlen(argv[i]) + 1);
        my_copy(array[ind], argv[i]);
        ind++;
    } 

    int file_d = open(argv[2], O_RDONLY);
    file_data xf;
    char* cont;
    int* fd_array = malloc(sizeof(int) * argc - 3);
    int l = 0;

    while(read(file_d, &xf, 512))
    {
        if((compare(xf.magic, "ustar  ")) == 0 && check_file(array, xf.name) == 1)
        { 
            creat(xf.name, 000644);
            int size = atoi(xf.size);
            size = octalToDecimal(size);
            cont = malloc(sizeof(char) * size);
            fill_with_null(cont, size);
            my_copy(cont, content(&xf, file_d));
            fd_array[l] = open(xf.name, O_WRONLY | O_APPEND);
            write(fd_array[l], cont, size);
            l++; 
            free(cont);
        }
    }
    free(array);
    for(int i = 0; i < argc - 3; i++)
        close(fd[i]);
    free(fd);
    close(file_d);
    for(int i = 0; i < argc - 3; i++)
        close(fd_array[i]);
    free(fd_array);
}

void check_modification(char* name, char* tar, list* files)
{
    file_data header;
    int fd = open(tar, O_RDWR| O_APPEND);
    struct stat fs;
    stat(name, &fs);
    int j = 0;
    while(read(fd, &header, 512))
    {
        if(compare(header.magic, "ustar  ") == 0 && header.typeflag == '0' && compare(header.name, name) == 0)
        {
            j = 1;
            char* oct = malloc(sizeof(char) * 12);
            fill_with_null(oct, 12);
            oct = dec_to_octal(fs.st_mtim.tv_sec, 12);
            if(compare(oct, header.mtime) == 1)
            {
                j = 2;
            }
        }
    }

    if(j == 2 || j == 0){
        fill_header(&header);
        fill_with_data(&header, files);
        write(fd, &header, 512);
        get_content(files, fd);
    }
    close(fd);
}

void uf_option(int argc, char** argv)
{
    int fd = open(argv[2], O_APPEND | O_WRONLY);
    list* files = NULL;
    for(int i = 3; i < argc; i++)
    {
        add_last(&files, argv[i]);
    }
    close(fd);
    while(files)
    {
        check_modification(files->file_name, argv[2], files);
        files = files->next;
    }
}

void checkin_input(int argc,char** argv)
{
    int i = 1;
    if(argv[i])
    {
        if(compare("-cf", argv[i]) == 0)
        {
            cf_option(argc, argv);
            return;
        }
        else if(compare("-tf", argv[i]) == 0)
        {
            ts_option(argc, argv, 0);
            return;
        }
        else if(compare("-rf", argv[i]) == 0)
        {
            rf_option(argc, argv);
            return;
        }
        else if(compare("-xf", argv[i]) == 0)
        {
            xf_option(argc, argv);
            return;
        }
        else if(compare("-uf", argv[i]) == 0)
        {
            uf_option(argc, argv);
            return;
        }
    }
}

int main(int argc, char** argv)
{   
    checkin_input(argc, argv);
    return 0;
}
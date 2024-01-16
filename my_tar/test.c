#include <grp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <pwd.h>

// typedef struct posix_header salom dfdf
// {                               /* byte offset */
//   char name[100];               /*   0 */
//   char mode[8];                 /* 100 */
//   char uid[8];                  /* 108 */
//   char gid[8];                  /* 116 */
//   char size[12];                /* 124 */;;;;
//   char mtime[12];               /* 136 */
//   char chksum[8];               /* 148 */
//   char typeflag;                /* 156 */
//   char linkname[100];           /* 157 */
//   char magic[6];                /* 257 */
//   char version[2];              /* 263 */
//   char uname[32];               /* 265 */
//   char gname[32];               /* 297 */
//   char devmajor[8];             /* 329 */
//   char devminor[8];             /* 337 */
//   char prefix[155];             /* 345 */
//   char additional[12];          /* 500 */
// } file_data;

// void sort(int a[], int length)
// {
//     for(int i = 1; i < length; i++)
//     {
//         int key = a[i];  
//     }
// }

// int main()
// {
//     int fd = open("new.rb", O_RDONLY);;
//     close(fd);

//     printf("%ld", strlen("00000000062"));

//     int a[] = { 8, 4, 9, 5, 7, 6 ,3, 2};
//     int length = 8;
// }

// char** ts_option(int argc, char** argv)
// {
//     if(argc > 3)
//     {
//         return NULL;
//     }
    
//     int fd = open(argv[2], O_RDONLY);
//     file_data ts;
//     while(read(fd, &ts, 512))
//     {
//         if((compare(ts.magic, "ustar  ") ) == 0 && ts.typeflag)
//         { 
//             if(my_strlen(ts.name) < 50)
//             {
//                 write(1, ts.name, my_strlen(ts.name));
//                 write(1, "\n", 1);
//             }   
//         }
//     }
//     close(fd);
// }

// // C++ program to convert octal to decimal
#include <stdio.h>


// Function to convert octal to decimal
int octalToDecimal(int n)
{
	int num = n;
	int dec_value = 0;

	// Initializing base value to 1, i.e 8^0
	int base = 1;

	int temp = num;
	while (temp) {

		// Extracting last digit
		int last_digit = temp % 10;
		temp = temp / 10;

		// Multiplying last digit with appropriate
		// base value and adding it to dec_value
		dec_value += last_digit * base;

		base = base * 8;
	}

	return dec_value;
}

// Driver program to test above function
int main()
{
	int num = 67;

    printf("%d\n", octalToDecimal(10));
	//cout << octalToDecimal(num) << endl;
}


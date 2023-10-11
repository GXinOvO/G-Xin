/*************************************************************************
	> File Name: 1.myls.c
	> Author: 
	> Mail: 
	> Created Time: Wed 07 Dec 2022 07:36:28 PM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

int ls_la(char *dpath) {
    //opendir()获取dpath目录下所有文件和目录的列表，
    //如果dpath是个文件或者失败返回NULL
    DIR *dir = opendir(dpath);
    if(dir == NULL) {
        closedir(dir);
        return -1;
    }
    struct dirent *dirent;
    //stat数据结构可以获取文件名为d_name的文件的详细信息，通过stat函数
    struct stat statbuf;

    //readdir()可以返回opendir返回的那个列表
    while((dirent = readdir(dir)) != NULL) {
        stat(dirent->d_name, &statbuf);
        //类型
        char mode = '-';
        switch(statbuf.st_mode & S_IFMT) {
            case  S_IFSOCK:
                mode = 's';
                break;
            case S_IFLNK:
                mode = 'l';
                break;
            case S_IFREG:
                mode = '-';
                break;
            case S_IFBLK:
                mode = 'b';
                break;
            case S_IFDIR:
                mode = 'd';
                break;
            case S_IFCHR:
                mode = 'c';
                break;
            case S_IFIFO:
                mode = 'p';
                break;
            default :
                mode = 'u';
                break;
        }

        //权限
        char permission[10] = "---------";
        permission[0] = statbuf.st_mode & S_IRUSR ? 'r' : '-';
        permission[1] = statbuf.st_mode & S_IWUSR ? 'w' : '-';
        permission[2] = statbuf.st_mode & S_IXUSR ? 'x' : '-';
        permission[3] = statbuf.st_mode & S_IRGRP ? 'r' : '-';
        permission[4] = statbuf.st_mode & S_IWGRP ? 'w' : '-';
        permission[5] = statbuf.st_mode & S_IXGRP ? 'x' : '-';
        permission[6] = statbuf.st_mode & S_IROTH ? 'r' : '-';
        permission[7] = statbuf.st_mode & S_IWOTH ? 'w' : '-';
        permission[8] = statbuf.st_mode & S_IXOTH ? 'x' : '-';

        permission[2] = statbuf.st_mode & S_ISUID ? (permission[2] == 'x' ? 's' : 'S') : permission[2];
        permission[5] = statbuf.st_mode & S_ISGID ? (permission[5] == 'x' ? 's' : 'S') : permission[5];
        permission[8] = statbuf.st_mode & S_ISVTX ? (permission[8] == 'x' ? 't' : 'T') : permission[8];
        //链接数

        //所属者
        //getpwuid()返回user ID对应的passwd结构体指针
        struct passwd *pwd = getpwuid(statbuf.st_uid);
        
        //所属组
        struct group *grp = getgrgid(statbuf.st_gid);
        
        //大小
        
        //mtime时间
        struct tm *time = localtime(&statbuf.st_mtime);
        char *month;
        switch(time->tm_mon + 1) {
            case 1:
                month = "Jan";
                break;
            case 2:
                month = "Feb";
                break;
            case 3:
                month = "Mar";
                break;
            case 4:
                month = "Apr";
                break;
            case 5:
                month = "May";
                break;
            case 6:
                month = "Jun";
                break;
            case 7:
                month = "Jul";
                break;
            case 8:
                month = "Aug";
                break;
            case 9:
                month = "Sep";
                break;
            case 10:
                month = "Oct";
                break;
            case 11:
                month = "Nov";
                break;
            case 12:
                month = "Dec";
                break;
            default:
                fprintf(stderr, "unknown\n");
                exit(1);
        }
        //文件名字
        printf("%c%s %2ld %s %s %7ld %ld %s %2d:%2d %s\n",
               mode,
               permission,
               statbuf.st_nlink,
               pwd->pw_name,
               grp->gr_name,
               statbuf.st_size,
               statbuf.st_mtime,
               month,
               time->tm_mday,
               time->tm_min,
               dirent->d_name
              );
    }
    closedir(dir);
    return 0;
}

int main(int argc, char *argv[]) {
    
    char *dpath = NULL;
    if(argc == 1) {
        dpath = ".";
    }else if(argc == 2) {
        dpath = argv[1];
    }else {
        fprintf(stderr, "Usage : %s [directory]\n", argv[0]);
        exit(1);
    }
    
    if(ls_la(dpath) < 0) {
        perror("ls_la");
        exit(1);
    }

    //printf("path = %s\n", dpath);
    return 0;
}

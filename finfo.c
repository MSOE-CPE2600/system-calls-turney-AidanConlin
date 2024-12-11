/**********************************************
*  Filename: finfo.c
*  Description: A program that displays detailed information about a specified 
*  file, including permissions, owner, group, size, and last modification time.
*
*  Author: Aidan Conlin
*  Class: CPE 2600 121
*  Date: 12/8/2024
*  Note: gcc -o finfo finfo.c -Wall -Wextra
***********************************************/
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <errno.h>

/**
 * @brief Formats the file's permissions into a human-readable string.
 * Converts the mode bits of a file into a string representation showing
 * file type (directory, regular file, symbolic link) and access permissions.
 *
 * @param mode The file mode (from `stat.st_mode`).
 * @param buffer A character array to store the formatted permissions string.
 */
void format_permissions(mode_t mode, char* buffer) {
    buffer[0] = (S_ISDIR(mode)) ? 'd' : (S_ISLNK(mode)) ? 'l' : '-';
    buffer[1] = (mode & S_IRUSR) ? 'r' : '-';
    buffer[2] = (mode & S_IWUSR) ? 'w' : '-';
    buffer[3] = (mode & S_IXUSR) ? 'x' : '-';
    buffer[4] = (mode & S_IRGRP) ? 'r' : '-';
    buffer[5] = (mode & S_IWGRP) ? 'w' : '-';
    buffer[6] = (mode & S_IXGRP) ? 'x' : '-';
    buffer[7] = (mode & S_IROTH) ? 'r' : '-';
    buffer[8] = (mode & S_IWOTH) ? 'w' : '-';
    buffer[9] = (mode & S_IXOTH) ? 'x' : '-';
    buffer[10] = '\0';
}

/**
 * @brief Retrieves the username of a file's owner.
 *
 * Uses getpwuid() to resolve the owner's user ID into a username.
 *
 * @param uid The user ID of the file's owner.
 * @return The username of the file owner, or "Unknown" if not found.
 */
const char* get_username(uid_t uid) {
    struct passwd* pw = getpwuid(uid);
    return (pw != NULL) ? pw->pw_name : "Unknown";
}

/**
 * @brief Retrieves the group name of a file's owner.
 *
 * Uses getgrgid() to resolve the owner's group ID into a group name.
 *
 * @param gid The group ID of the file's owner.
 * @return The group name, or "Unknown" if not found.
 */
const char* get_groupname(gid_t gid) {
    struct group* grp = getgrgid(gid);
    return (grp != NULL) ? grp->gr_name : "Unknown";
}

/**
 * @brief Takes a file path as a command-line argument, retrieves the file's metadata 
 * using stat(), and displays the file size, permissions, owner, group, and last
 * modification time in a human-readable format.
 *
 * @param argc The number of command-line arguments.
 * @param argv The command-line arguments.
 * @return 0 on successful execution, or 1 on failure.
 */
int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file_path>\n", argv[0]);
        return 1;
    }

    const char* file_path = argv[1];
    struct stat file_stat;

    if (stat(file_path, &file_stat) == -1) {
        perror("stat");
        return 1;
    }

    char permissions[11];
    format_permissions(file_stat.st_mode, permissions);

    const char* username = get_username(file_stat.st_uid);
    const char* groupname = get_groupname(file_stat.st_gid);

    char mod_time[20];
    struct tm* timeinfo = localtime(&file_stat.st_mtime);
    strftime(mod_time, sizeof(mod_time), "%Y-%m-%d %H:%M:%S", timeinfo);

    printf("File: %s\n", file_path);
    printf("Size: %lld bytes\n", (long long)file_stat.st_size);
    printf("Permissions: %s\n", permissions);
    printf("Owner: %s\n", username);
    printf("Group: %s\n", groupname);
    printf("Last modified: %s\n", mod_time);

    return 0;
}

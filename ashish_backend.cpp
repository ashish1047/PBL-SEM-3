#include <iostream>
using namespace std;

#define PATH_SIZE 100
#define BUFFER_SIZE 1024

class FileBackup
{
private:
    char sourcePath[PATH_SIZE];
    char backupPath[PATH_SIZE];

public:
    void getPaths()
    {
        printf("Enter source file name (example: settings.txt): ");
        scanf("%99s", sourcePath);

        printf("Enter backup file name (example: settings_backup.txt): ");
        scanf("%99s", backupPath);
    }

    int scanFile()
    {
        FILE *source = fopen(sourcePath, "rb");

        if (source == NULL)
        {
            printf("Source file could not be opened.\n");
            return 0;
        }

        printf("Source file found and opened successfully.\n");
        fclose(source);
        return 1;
    }

    int createBackup()
    {
        FILE *source = fopen(sourcePath, "rb");

        if (source == NULL)
        {
            printf("Error opening source file.\n");
            return 0;
        }

        FILE *backup = fopen(backupPath, "wb");

        if (backup == NULL)
        {
            printf("Error creating backup file.\n");
            fclose(source);
            return 0;
        }

        char buffer[BUFFER_SIZE];
        size_t bytesRead;

        while ((bytesRead = fread(buffer, 1, BUFFER_SIZE, source)) > 0)
        {
            size_t bytesWritten = fwrite(buffer, 1, bytesRead, backup);

            if (bytesWritten != bytesRead)
            {
                printf("Error writing backup file.\n");
                fclose(source);
                fclose(backup);
                return 0;
            }
        }

        fclose(source);
        fclose(backup);

        printf("Backup created successfully.\n");
        return 1;
    }
};

int main()
{
    FileBackup file;
    file.getPaths();

    if (file.scanFile())
        file.createBackup();

    return 0;
}

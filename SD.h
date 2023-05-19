#ifndef SD_H_
#define SD_H_

#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define FILE_READ "r"
#define FILE_WRITE "w"
#define O_READ "r"
#define O_WRITE "w"
const uint8_t SD_CHIP_SELECT_PIN = 0;

namespace SDLib{

class File final {
private:
    FILE * _file;
    char * _filename;
    char * _mode;
    long int _position;
    int _size;
public:
    File(const char *, const char *);
    File() = delete;
    ~File();

    size_t write(char);
    size_t write(const char *, size_t);

    int availableForWrite();
    int read();
    int peek();
    int available();
    void flush();
    int read(void *, uint16_t);
    bool seek(uint32_t);
    uint32_t position()const;
    uint32_t size()const;
    void close();
    operator bool()const;
    char *name()const;

};

class SDClass{
private:

    bool _running = false;
    DIR * _dir;
    friend class File;

public:

    ~SDClass();

    bool begin(uint8_t = SD_CHIP_SELECT_PIN);
    bool begin(uint32_t, uint8_t);

    void end();

    File open(const char *, const char *);
    
    bool exists(const char *);

    bool mkdir(const char *);

    bool remove(const char *);

    bool rmdir(const char *);

};

extern SDClass SD;

};

typedef SDLib::File SDFile;
typedef SDLib::SDClass SDFileSystemClass;
#define SDFileSystem SDLib::SD

using namespace SDLib;

#endif
#include "SD.h"

namespace SDLib{

File::File(){
    this->_filename = new char[1];
    this->_mode = new char[1];

    this->_position = 0;
    this->_size = 0;

    this->_file = NULL;
}

File::File(const char * filename, int mode){
    char mode_c = ((char)mode);
    this->_filename = new char[strlen(filename) + 1];
    this->_mode = new char[strlen(&mode_c) + 1];

    strcpy(this->_filename, filename);
    strcpy(this->_mode, &mode_c);

    this->_position = 0;
    this->_size = 0;

    this->_file = fopen(filename, this->_mode);
}

File& File::operator=(const File& f){
    this->_filename = new char[strlen(f._filename) + 1];
    this->_mode = new char[strlen(f._mode) + 1];

    strcpy(this->_filename, f._filename);
    strcpy(this->_mode, f._mode);

    this->_position = 0;
    this->_size = 0;

    this->_file = fopen(this->_filename, this->_mode);

    return *this;
}

size_t File::write(const char *buf, size_t n_bytes){
    if(!(this->_file)){
        return 0;
    }
    this->_size += n_bytes;
    fprintf(this->_file, "%s", buf);
    return n_bytes;
}

size_t File::write(const char *buf){
    if(!(this->_file)){
        return 0;
    }
    this->_size += strlen(buf);
    fprintf(this->_file, "%s", buf);
    return strlen(buf);
}

size_t File::write(char c){
    ++(this->_size);
    return write(&c, 1);
}

int File::availableForWrite(){
    if(!(this->_file)){
        return 0;
    }
    return 1;
}

int File::read(){
    if(!(this->_file)){
        return 0;
    }
    ++(this->_position);
    return fgetc(this->_file);
}

int File::peek(){
    int c;
    c = fgetc(this->_file);
    ungetc(c, this->_file);
    return c;
}

int File::available(){
    if(!(this->_file)){
        return 0;
    }
    if(peek() != EOF){
        return 1;
    }
    return 0;
}

void File::flush(){
    // if(this->_file){
    //     rewind(this->_file);
    // }
    // this->_position = 0;
}

int File::read(void *buf, uint16_t size){
    int i = 0;
    char * b = (char *)buf;
    while(i < size){
        char c = read();
        b[i] = c;
        ++(this->_position);
    }
    return i;
}

bool File::seek(uint32_t pos){
    if(!(this->_file)){
        return false;
    }
    fseek(this->_file, pos, SEEK_SET);
    this->_position = pos;
    return true;
}

uint32_t File::position()const{
    if(!(this->_file)){
        return -1;
    }
    return this->_position;
}

uint32_t File::size()const{
    return this->_size;
}

void File::close(){
    fclose(this->_file);
    this->_file = NULL;
    delete [] _filename;
    delete [] _mode;
    this->_position = 0;
    this->_size = 0;
}

File::operator bool()const{
    return this->_file;
}

char * File::name()const{
    return this->_filename;
}

File::~File(){}

bool File::rename(const char *oldName, const char *newName){
    return ::rename(oldName, newName);
}

bool File::isDirectory(){
    struct stat path_stat;
    stat(this->_filename, &path_stat);
    return S_ISREG(path_stat.st_mode);
}

File File::openNextFile(uint8_t mode){
    return File();
}

void File::rewindDirectory(){}


};
#include "SD.h"

namespace SDLib{

    bool SDClass::begin(uint8_t csPin){
        this->_dir = opendir(".");

        if(this->_dir == NULL){
            return false;
        }

        this->_running = true;
        return true;
    }

    bool SDClass::begin(uint32_t clock, uint8_t csPin){
        this->_dir = opendir(".");

        if(this->_dir == NULL){
            return false;
        }

        this->_running = true;
        return true;
    }

    void SDClass::end(){
        this->_dir = NULL;
        this->_running = false;
    }

    File SDClass::open(const char * filename, const char * mode){
        if(this->_running){
            return File(filename, mode);
        }

        return;
    }

    bool SDClass::exists(const char *filename){
        if(!this->_running){
            return false;
        }
        if(this->_dir == NULL){
            return false;
        }
        struct dirent *de;
        while((de = readdir(this->_dir)) != NULL){
            if(strcmp(filename, de->d_name) == 0){
                return true;
            }
        }
        return false;
    }

    bool SDClass::mkdir(const char * dir){
        if(!this->_running){
            return false;
        }
        struct stat st;
        if(stat(dir, &st) == -1){
            ::mkdir(dir, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
        }else{
            return false;
        }
        return true;      
    }

    bool SDClass::remove(const char * filename){
        if(!this->_running){
            return false;
        }
        return ::remove(filename) + 1;
    }

    bool SDClass::rmdir(const char * filepath){
        if(!this->_running){
            return false;
        }
        return ::rmdir(filepath) + 1;
    }

    SDClass::~SDClass(){
        if(this->_dir != NULL){
            closedir(this->_dir);
        }
    }

    SDClass SD;

};
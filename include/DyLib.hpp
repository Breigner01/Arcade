#pragma once

#include "Exception.hpp"
#include <string>
#include <dlfcn.h>

template<typename T>
class DyLib
{
private:
    void *m_handle{nullptr};
    T *m_lib{nullptr};
public:

    DyLib() noexcept = default;
    DyLib(const std::string &path)
    {
        this->loadLib(path);
    }
    ~DyLib()
    {
        this->releaseLib();
    }

    DyLib(const DyLib&) = delete;
    DyLib(DyLib &&) = delete;
    DyLib& operator=(const DyLib&) = delete;
    DyLib& operator=(DyLib &&) = delete;

    void loadLib(const std::string &path)
    {
        this->releaseLib();
        m_handle = dlopen(path.c_str(), RTLD_NOW | RTLD_LOCAL);
        if (!m_handle)
            throw Arcade::exception(dlerror());
        void *t = dlsym(m_handle, "entry_point");
        if (!t)
            throw Arcade::exception(dlerror());
        m_lib = ((T *(*)()) t)();
    }
    void releaseLib()
    {
        delete m_lib;
        if (m_handle)
            dlclose(m_handle);
        m_handle = nullptr;
    }
    T *get() {return m_lib;}
};
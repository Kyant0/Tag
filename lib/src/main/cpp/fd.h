#ifndef TAG_FD_H
#define TAG_FD_H

#include <unistd.h>

class UniqueFileDescriptor {
public:
    UniqueFileDescriptor(int fd) : m_fd(fd) {}
    ~UniqueFileDescriptor() {
        close();
    }

    UniqueFileDescriptor(const UniqueFileDescriptor&) = delete;
    UniqueFileDescriptor& operator=(const UniqueFileDescriptor&) = delete;

    UniqueFileDescriptor(UniqueFileDescriptor&& other) noexcept {
        m_fd = other.m_fd;
        other.m_fd = -1;
    }

    UniqueFileDescriptor& operator=(UniqueFileDescriptor&& other) noexcept {
        if (this != &other) {
            close();
            m_fd = other.m_fd;
            other.m_fd = -1;
        }
        return *this;
    }

    int get() const {
        return m_fd;
    }

private:
    void close() {
        if (m_fd != -1) {
            ::close(m_fd);
            m_fd = -1;
        }
    }

    int m_fd;
};

std::string getFilePathFromFd(int fd) {
    char procPath[PATH_MAX];
    snprintf(procPath, sizeof(procPath), "/proc/self/fd/%d", fd);

    char filePath[PATH_MAX];
    ssize_t len = readlink(procPath, filePath, sizeof(filePath) - 1);
    if (len == -1) {
        perror("readlink");
        return "";
    }
    filePath[len] = '\0';

    return std::string(filePath);
}

#endif //TAG_FD_H

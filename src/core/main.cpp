#include <src/core/ZiaCore/ZiaCore.hpp>

int main(int argc, char *argv[]) {
    ZiaCore ziaCore;
    ziaCore.processParams(argc, argv);
    ziaCore.startZia();
}
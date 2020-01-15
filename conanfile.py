from conans import ConanFile, CMake, MSBuild
import os

class CPP_zia(ConanFile):
    name = "zia"
    version = "0.1"
    settings = "os_build", "compiler", "build_type", "arch"
    requires = "boost/1.71.0@conan/stable"
    generators = "cmake", "visual_studio"

    def build(self):
        if platform.system() == "Windows":
            compiler="Visual Studio"
            compiler.version=16
            compiler.toolset=v142
            msbuild = MSBuild(self)
            msbuild.build("MyZia.sln")
        else:
            cmake = CMake(self)
            cmake.configure()
            cmake.build()
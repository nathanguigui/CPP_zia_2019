from conans import ConanFile, CMake, MSBuild
import os

class CPP_zia(ConanFile):
    name = "zia"
    version = "0.1"
    settings = "os", "os_build", "compiler", "build_type", "arch"
    requires = "boost/1.71.0@conan/stable", "jsoncpp/1.9.2"
    generators = "cmake", "visual_studio"

    def build_requirements(self):
        if self.settings.os == "Windows" or self.settings.os == "Macos":
            self.build_requires("OpenSSL/1.1.1@conan/stable")

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

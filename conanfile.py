from conan import ConanFile
from conan.tools.system.package_manager import Apt, Yum, Zypper, Pkg, Chocolatey

class GraphicsLibraries(ConanFile):
    build_policy = "missing"
    generators =("CMakeToolchain", "CMakeDeps")
    settings = ("os", "build_type", "arch", "compiler")

    def requirements(self):
        self.requires("opengl/system")
        #if self.settings.os == "Linux" or self.settings.os == "FreeBSD":
            #self.requires("xorg/system")
        self.requires("glew/2.2.0")
        self.requires("glfw/[>=3.0]")

    def build_requirements(self):
        self.tool_requires("cmake/[>=3.25]")

    def layout(self):
        self.folders.generators = ""

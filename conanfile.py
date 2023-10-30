from conans import ConanFile, CMake

# python3 `which conan` create . demo/testing -o gem5:python_config="/usr/bin/python3-config"
# conan create ../ demo/testing -pr gcc91 -s compiler.cppstd=20
# python3 `which conan` install -o gem5:python_config="/usr/bin/python3-config"
# conan create .. demo/debug --build=missing -s compiler.cppstd=20 -tf None -pr gcc91


class TLMTestConan(ConanFile):
    name = 'tlm_test'
    description = 'TLM test'
    settings = "os", "compiler", "build_type", "arch"
    options = {
        "fPIC": [True, False],
        "CONANPKG": ["ON", "OFF"],
        "shared": [True, False],
        "build_tool": ["cmake", "scons"]
    }
    default_options = {
        "fPIC": True,
        "CONANPKG": "OFF",
        "shared": True,
        "build_tool": "cmake"
    }
    version = "1.0"
    url = "https://github.com/intel-sandbox/cofluent_gem5_tlm_wrapper"
    license = "Proprietary"

    requires = ("systemc/2.3.3@syssim/stable")

    exports_sources = ("include/*", "src/*", "CMakeLists.txt")

    __cmake = None

    def requirements(self):
        pass

    def configure(self):
        self.generators = "cmake", "cmake_find_package"

    def build(self):
        self.build_cmake()

    def build_cmake(self):
        print("self.source_folder", self.source_folder)
        self._cmake.configure(source_dir=self.source_folder)
        self._cmake.build()

    @property
    def _cmake(self):
        if self.__cmake is None:
            self.__cmake = CMake(self)
        return self.__cmake
solution("cdust")

buildoptions({"-fPIC"})

configurations({"Debug", "Release"})
flags({"NoRTTI"})

configuration("Release")
flags({"OptimizeSpeed"})

configuration("Debug")
flags({"Symbols"})

configuration({})

function compile_java (files)
   command = "javac"
   for k,v in pairs(files) do
      command = command .. " java/" .. v
   end
   postbuildcommands({command})
end

project("dustshim")
kind("StaticLib")
language("C++")
buildoptions({"-std=c++11"})
links({"v8"})
includedirs({"src"})
files({"src/dust_renderer.cpp"
       , "src/result_store.cpp"
       , "src/out_streams.cpp"
})

project("cppdust")
kind("ConsoleApp")
language("C++")
buildoptions({"-std=c++11"})
links({"v8", "dustshim"})
includedirs({"src"})
files({"src/main.cpp"
})

project("cppperf")
kind("ConsoleApp")
language("C++")
buildoptions({"-std=c++11"})
links({"v8", "dustshim"})
includedirs({"src"})
files({"src/performance.cpp"
})

project("JDust")
kind("SharedLib")
language("C++")
buildoptions({"-std=c++11"})
links({"v8", "dustshim"})
includedirs({"/usr/lib/jvm/java-7-openjdk/include"
             , "/usr/lib/jvm/java-7-openjdk/include/linux"
             , "src"})
prebuildcommands({"cd java && javah buzz.fizz.jdust.JDust"})
targetdir("java")
files({"java/JDust.cpp"
       , "java/JStore.cpp"
})
compile_java({"buzz/fizz/jdust/JDust.java"
              , "buzz/fizz/jdust/JState.java"
              , "buzz/fizz/jdust/JPerformanceTest.java"})

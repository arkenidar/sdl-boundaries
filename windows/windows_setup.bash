# app bundler in windows and wine platforms (cross-platform)

# uses depends.exe for listing DLL files: https://dependencywalker.com/
# tested in to check also this platform: https://www.winehq.org/

# this is the app directory (in MSYS + MINGW style for directories)
app_dir=/c/opt/dropbox/gh-repos/_group_sdl/sdl-boundaries

# locate the main exe file:
# see your build system and IDE settings,
# currently CLion as IDE -> $app_dir/cmake-build-debug
cp "$app_dir/cmake-build-debug/app.exe" .
# files used by such exe file (see dependencywalker.com)
cp -r "$app_dir/assets" .
# ... then DLL files for the exe and dll hierarchy (depends.exe)

# SDL2: https://www.libsdl.org/ in MSYS + MINGW
cp "c:\msys64\mingw64\bin\SDL2.dll" .
# SDL2_image.dll has many dependencies
cp "c:\msys64\mingw64\bin\SDL2_image.dll" .
cp "c:\msys64\mingw64\bin\LIBJPEG-8.DLL" .
cp "c:\msys64\mingw64\bin\LIBGCC_S_SEH-1.DLL" .
cp "c:\msys64\mingw64\bin\LIBWINPTHREAD-1.DLL" .
cp "c:\msys64\mingw64\bin\LIBJXL.DLL" .
cp "c:\msys64\mingw64\bin\LIBSTDC++-6.DLL" .
cp "c:\msys64\mingw64\bin\LIBBROTLIDEC.DLL" .
cp "c:\msys64\mingw64\bin\LIBBROTLICOMMON.DLL" .
cp "c:\msys64\mingw64\bin\LIBBROTLIENC.DLL" .
cp "c:\msys64\mingw64\bin\LIBHWY.DLL" .
cp "c:\msys64\mingw64\bin\LIBLCMS2-2.DLL" .
cp "c:\msys64\mingw64\bin\LIBPNG16-16.DLL" .
cp "c:\msys64\mingw64\bin\ZLIB1.DLL" .
cp "c:\msys64\mingw64\bin\LIBTIFF-6.DLL" .
cp "c:\msys64\mingw64\bin\LIBDEFLATE.DLL" .
cp "c:\msys64\mingw64\bin\LIBJBIG-0.DLL" .
cp "c:\msys64\mingw64\bin\LIBLERC.DLL" .
cp "c:\msys64\mingw64\bin\LIBLZMA-5.DLL" .
cp "c:\msys64\mingw64\bin\LIBZSTD.DLL" .
cp "c:\msys64\mingw64\bin\LIBWEBP-7.DLL" .
cp "c:\msys64\mingw64\bin\LIBSHARPYUV-0.DLL" .

# app bundler in windows and wine platforms (cross-platform)

# uses depends.exe for listing DLL files: https://dependencywalker.com/
# tested in to check also this platform: https://www.winehq.org/

# this is the app directory (in MSYS + MINGW style for directories)
app_dir=..
dest_dir=app-distrib

# locate the main exe file:
# see your build system and IDE settings,
# currently CLion as IDE -> $app_dir/cmake-build-debug
cp "$app_dir/cmake-build-debug/app.exe" "$dest_dir"
# files used by such exe file (see dependencywalker.com)
cp -r "$app_dir/assets" "$dest_dir"
# ... then DLL files for the exe and dll hierarchy (depends.exe)

# SDL2: https://www.libsdl.org/ in MSYS + MINGW
cp "c:\msys64\mingw64\bin\SDL2.dll" "$dest_dir"
# SDL2_image.dll has many dependencies
cp "c:\msys64\mingw64\bin\SDL2_image.dll" "$dest_dir"
cp "c:\msys64\mingw64\bin\LIBJPEG-8.DLL" "$dest_dir"
cp "c:\msys64\mingw64\bin\LIBGCC_S_SEH-1.DLL" "$dest_dir"
cp "c:\msys64\mingw64\bin\LIBWINPTHREAD-1.DLL" "$dest_dir"
cp "c:\msys64\mingw64\bin\LIBJXL.DLL" "$dest_dir"
cp "c:\msys64\mingw64\bin\LIBSTDC++-6.DLL" "$dest_dir"
cp "c:\msys64\mingw64\bin\LIBBROTLIDEC.DLL" "$dest_dir"
cp "c:\msys64\mingw64\bin\LIBBROTLICOMMON.DLL" "$dest_dir"
cp "c:\msys64\mingw64\bin\LIBBROTLIENC.DLL" "$dest_dir"
cp "c:\msys64\mingw64\bin\LIBHWY.DLL" "$dest_dir"
cp "c:\msys64\mingw64\bin\LIBLCMS2-2.DLL" "$dest_dir"
cp "c:\msys64\mingw64\bin\LIBPNG16-16.DLL" "$dest_dir"
cp "c:\msys64\mingw64\bin\ZLIB1.DLL" "$dest_dir"
cp "c:\msys64\mingw64\bin\LIBTIFF-6.DLL" "$dest_dir"
cp "c:\msys64\mingw64\bin\LIBDEFLATE.DLL" "$dest_dir"
cp "c:\msys64\mingw64\bin\LIBJBIG-0.DLL" "$dest_dir"
cp "c:\msys64\mingw64\bin\LIBLERC.DLL" "$dest_dir"
cp "c:\msys64\mingw64\bin\LIBLZMA-5.DLL" "$dest_dir"
cp "c:\msys64\mingw64\bin\LIBZSTD.DLL" "$dest_dir"
cp "c:\msys64\mingw64\bin\LIBWEBP-7.DLL" "$dest_dir"
cp "c:\msys64\mingw64\bin\LIBSHARPYUV-0.DLL" "$dest_dir"
# SDL2_TTF.DLL and its dependencies
cp "c:\msys64\mingw64\bin\SDL2_TTF.DLL" "$dest_dir"
cp "c:\msys64\mingw64\bin\LIBFREETYPE-6.DLL" "$dest_dir"
cp "c:\msys64\mingw64\bin\LIBBZ2-1.DLL" "$dest_dir"
cp "c:\msys64\mingw64\bin\LIBHARFBUZZ-0.DLL" "$dest_dir"
cp "c:\msys64\mingw64\bin\LIBGLIB-2.0-0.DLL" "$dest_dir"
cp "c:\msys64\mingw64\bin\LIBPCRE2-8-0.DLL" "$dest_dir"
cp "c:\msys64\mingw64\bin\LIBGRAPHITE2.DLL" "$dest_dir"
cp "c:\msys64\mingw64\bin\LIBINTL-8.DLL" "$dest_dir"
cp "c:\msys64\mingw64\bin\LIBICONV-2.DLL" "$dest_dir"

# cp "" "$dest_dir"

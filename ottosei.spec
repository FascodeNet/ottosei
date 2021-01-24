%define dist .el64

Summary: ottosei
Name: ottosei
Version: 1.0.1
Release: 1
Group: System Environment/Shells
License: NONE
Packager: kokkiemouse
Vendor: INDETAIL

Source0: https://github.com/FascodeNet/ottosei/archive/master.tar.gz
BuildRequires: cmake,ninja-build,clang
Requires: mpg123,jp2a,ImageMagick
%global debug_package %{nil}
%description
ottosei
%prep
rm -rf %{buildroot}

%setup -n ottosei-master

%build
mkdir -p build
cd build
cmake -G Ninja -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_INSTALL_PREFIX=%{buildroot} ..
ninja 
%install
cd build
ninja install
%clean
rm -rf %{buildroot}
%files
/usr/share/serene/ottosei/
/usr/bin/ottosei
%changelog
* Sun Nov 15 2020 kokkiemouse <kokkiemouse@fascode.net> 1.0.1-1 
- fixed background bug

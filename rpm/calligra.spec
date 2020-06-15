Name:           calligra
Version:        3.1.0+git18
Release:        1
Summary:        Calligra suite
License:        GPLv2
Url:            http://www.kde.org/
Source0:        %{name}-%{version}.tar.gz
BuildRequires:  cmake
BuildRequires:  bison
BuildRequires:  flex
BuildRequires:  boost-devel
BuildRequires:  libeigen3-devel
BuildRequires:  pkgconfig(icu-i18n)
BuildRequires:  pkgconfig(Qt5OpenGL)
BuildRequires:  pkgconfig(Qt5Quick)
BuildRequires:  pkgconfig(shared-mime-info)
BuildRequires:  extra-cmake-modules >= 5.34.0

Patch1: kconfigwidgets-no-kauth.patch
Patch2: kservices-no-krash.patch
Patch3: kio-no-solid.patch
Patch4: kxmlgui-no-textwidgets.patch
Patch5: kxmlgui-disable_startup_functions.patch
Patch6: k18n-disable-q_coreapp_startup_function.patch
Patch7: kdiagram-build-qreal-float.patch
Patch8: calligra-fake-kde4libs.patch
Patch9: calligra-stage.patch

# to be arrange for later upstream
Patch10: calligra-find.patch
Patch11: calligra-buildsystem.patch
Patch12: calligra-libs.patch
Patch13: calligra-plugins.patch
Patch14: calligra-error-reporting.patch
Patch15: calligra-sheets.patch
# to be removed after Qt upgrade
Patch16: calligra-sheets-read-time.patch
Patch18: calligra-cache.patch
Patch19: calligra-qtdbus.patch
Patch20: calligra-background.patch
Patch21: calligra-invalidate-cache.patch

Patch22: calligra-sheets-csvimport.patch

%description
%{summary}.

%package components
Summary: Qt Quick components for showing documents using Calligra
Requires: %{name}-libs
Requires: %{name}-data
Requires: %{name}-sheets-core
Requires: %{name}-words-core
Requires: %{name}-stage-core
%description components
%{summary}.

%package data
Summary: Calligra shared data
%description data
%{summary}.

%package filters
Summary: Calligra input/output filters
Requires: %{name}-libs
Obsoletes: %{name}-filters-libs < 3.1.0
Obsoletes: %{name}-sheets-filters < 3.1.0
Obsoletes: %{name}-words-filters < 3.1.0
Obsoletes: %{name}-stage-filters < 3.1.0
%description filters
%{summary}.

%post filters
/sbin/ldconfig
%postun filters -p /sbin/ldconfig

%package libs
Summary: Shared Calligra libraries
Requires: %{name}-kf5
%description libs
%{summary}.

%post libs
/sbin/ldconfig
%postun libs -p /sbin/ldconfig

%package plugins
Summary: Calligra plugins
%description plugins
%{summary}.

%post plugins
/sbin/ldconfig
%postun plugins -p /sbin/ldconfig

%package words-core
Summary: Calligra Words libraries
Requires: %{name}-plugins %{name}-data
%description words-core
%{summary}.

%post words-core
/sbin/ldconfig
%postun words-core -p /sbin/ldconfig

%package words-templates
Summary: Calligra Words templates
%description words-templates
%{summary}.

%package sheets-core
Summary: Calligra Sheets libraries
Requires: %{name}-plugins %{name}-data
Obsoletes: %{name}-sheets-core-plugins < 3.1.0
Obsoletes: %{name}-sheets-plugins < 3.1.0
%description sheets-core
%{summary}.

%post sheets-core
/sbin/ldconfig
%postun sheets-core -p /sbin/ldconfig

%package sheets-templates
Summary: Calligra Sheets templates
%description sheets-templates
%{summary}.

%package stage-core
Summary: Calligra Stage libraries
Requires: %{name}-plugins %{name}-data
Obsoletes: %{name}-stage-plugins < 3.1.0
%description stage-core
%{summary}.

%post stage-core
/sbin/ldconfig
%postun stage-core -p /sbin/ldconfig

%package stage-templates
Summary: Calligra Stage templates
%description stage-templates
%{summary}.

%package kf5
Summary:  Bundled KDE framework libraries
BuildRequires:  cmake
BuildRequires:  gettext
BuildRequires:  pkgconfig(Qt5Core)
BuildRequires:  qt5-qttools-linguist
BuildRequires:  pkgconfig(Qt5Network)
BuildRequires:  pkgconfig(Qt5DBus)
BuildRequires:  pkgconfig(Qt5Gui)
BuildRequires:  pkgconfig(Qt5Svg)
BuildRequires:  pkgconfig(Qt5Qml)
BuildRequires:  pkgconfig(Qt5Xml)
BuildRequires:  pkgconfig(Qt5Concurrent)
BuildRequires:  pkgconfig(Qt5Script)
BuildRequires:  pkgconfig(Qt5Test)
BuildRequires:  pkgconfig(Qt5Widgets)
BuildRequires:  pkgconfig(Qt5PrintSupport)
BuildRequires:  pkgconfig(KF5Archive)
BuildRequires:  python3-base
BuildRequires:  pkgconfig(zlib)
BuildRequires:  extra-cmake-modules >= 5.34.0
%description kf5
%{summary}


%prep
%setup -q -n %{name}-%{version}

%patch1 -d kconfigwidgets -p1
%patch2 -d kservice -p1
%patch3 -d kio -p1
%patch4 -d kxmlgui -p1
%patch5 -d kxmlgui -p1
%patch6 -d ki18n -p1
%patch7 -d kdiagram -p1
%patch8 -d upstream -p1
%patch9 -d upstream -p1
%patch10 -d upstream -p1
%patch11 -d upstream -p1
%patch12 -d upstream -p1
%patch13 -d upstream -p1
%patch14 -d upstream -p1
%patch15 -d upstream -p1
%patch16 -d upstream -p1
%patch18 -d upstream -p1
%patch19 -d upstream -p1
%patch20 -d upstream -p1
%patch21 -d upstream -p1
%patch22 -d upstream -p1

%define build_kf5() cd %1 ; if [ ! -d build ] ; then mkdir build ; fi ; cd build ; if [ ! -e Makefile ] ; then CMAKE_PREFIX_PATH=%{_buildrootdir}/kf5/usr cmake -DCMAKE_INSTALL_PREFIX=/usr -DCMAKE_INSTALL_RPATH=%{_libdir}/calligra-kf5 -DBUILD_TESTING=OFF %{?2} .. ; fi ; make %{?_smp_mflags} install DESTDIR=%{_buildrootdir}/kf5 ; cd ../.. ;
%build
%build_kf5 kcodecs
%build_kf5 kconfig
%build_kf5 kcoreaddons
%build_kf5 kdbusaddons
%build_kf5 kguiaddons
%build_kf5 kitemviews
%build_kf5 ki18n
%build_kf5 kwidgetsaddons
%build_kf5 kconfigwidgets "-DFORCE_DISABLE_KGLOBALACCEL=True"
%build_kf5 kcompletion
%build_kf5 kiconthemes
%build_kf5 kservice
%build_kf5 kio "-DKIOCORE_ONLY=True"
%build_kf5 kxmlgui
%build_kf5 kdiagram
if [ ! -d upstream/build ] ; then mkdir upstream/build ; fi ; cd upstream/build
CMAKE_PREFIX_PATH=%{_buildrootdir}/kf5/usr cmake -DCMAKE_INSTALL_PREFIX=/usr -DPRODUCTSET="PART_WORDS PART_STAGE PART_SHEETS PART_COMPONENTS FILTER_DOCX_TO_ODT FILTER_DOC_TO_ODT FILTER_RTF_TO_ODT FILTER_XLSX_TO_ODS FILTER_XLS_TO_SHEETS FILTER_PPTX_TO_ODP FILTER_PPT_TO_ODP PLUGIN_CHARTSHAPE PLUGIN_PATHSHAPES PLUGIN_VARIABLES FILTER_CSV_TO_SHEETS" -DBUILD_TESTING=OFF -DCMAKE_BUILD_TYPE=Release ..
make %{?_smp_mflags}

%install
install -d %{buildroot}%{_libdir}/calligra-kf5/
cp -a %{_buildrootdir}/kf5%{_libdir}/lib{KF5*,KChart}.so.* %{buildroot}%{_libdir}/calligra-kf5/
cd upstream/build
make install DESTDIR=%{buildroot}
install -d %{buildroot}%{_libdir}/qt5
if [ -d %{buildroot}%{_libdir}/qml ] ; then mv %{buildroot}%{_libdir}/qml %{buildroot}%{_libdir}/qt5/ ; fi
install -d %{buildroot}%{_libdir}/qt5/plugins
if [ -d %{buildroot}%{_libdir}/plugins/calligra ] ; then mv %{buildroot}%{_libdir}/plugins/calligra %{buildroot}%{_libdir}/qt5/plugins/ ; fi
if [ -d %{buildroot}%{_libdir}/plugins/calligrasheets ] ; then mv %{buildroot}%{_libdir}/plugins/calligrasheets %{buildroot}%{_libdir}/qt5/plugins/ ; fi
if [ -d %{buildroot}%{_libdir}/plugins/calligrastage ] ; then mv %{buildroot}%{_libdir}/plugins/calligrastage %{buildroot}%{_libdir}/qt5/plugins/ ; fi

%post -p /sbin/ldconfig
%postun -p /sbin/ldconfig

%files
%defattr(-,root,root,-)

%files components
%defattr(-,root,root,-)
%{_libdir}/qt5/qml/org/kde/calligra

%files data
%defattr(-,root,root,-)
%dir %{_datadir}/calligra
%{_datadir}/calligra/calligra_shell.rc
%{_datadir}/calligra/cursors
%{_datadir}/calligra/icons
%{_datadir}/calligra/palettes
%{_datadir}/calligra/pics
%{_datadir}/calligra/styles
%{_datadir}/icons/*

%files filters
%defattr(-,root,root,-)
%{_libdir}/qt5/plugins/calligra/formatfilters
%{_libdir}/libkomsooxml.so.*
%{_libdir}/libkoodf2.so.*
%{_libdir}/libkowv2.so.*
%{_libdir}/libRtfReader.so.*
%exclude %{_libdir}/libRtfReader.so
%exclude %{_libdir}/libkomsooxml.so
%exclude %{_libdir}/libkoodf2.so
%exclude %{_libdir}/libkowv2.so

%files libs
%defattr(-,root,root,-)
%{_libdir}/libbasicflakes.so.*
%{_libdir}/libflake.so.*
%{_libdir}/libkomain.so.*
%{_libdir}/libkoodf.so.*
%{_libdir}/libkopageapp.so.*
%{_libdir}/libkoplugin.so.*
%{_libdir}/libkostore.so.*
%{_libdir}/libkotext.so.*
%{_libdir}/libkotextlayout.so.*
%{_libdir}/libkoversion.so.*
%{_libdir}/libkowidgets.so.*
%{_libdir}/libkowidgetutils.so.*
%{_libdir}/libkundo2.so.*
%{_libdir}/libpigmentcms.so.*
%exclude %{_libdir}/libbasicflakes.so
%exclude %{_libdir}/libflake.so
%exclude %{_libdir}/libkomain.so
%exclude %{_libdir}/libkoodf.so
%exclude %{_libdir}/libkopageapp.so
%exclude %{_libdir}/libkoplugin.so
%exclude %{_libdir}/libkostore.so
%exclude %{_libdir}/libkotext.so
%exclude %{_libdir}/libkowidgets.so
%exclude %{_libdir}/libpigmentcms.so
%exclude %{_libdir}/libkotextlayout.so
%exclude %{_libdir}/libkowidgetutils.so
%exclude %{_libdir}/libkundo2.so
%exclude %{_libdir}/libkoversion.so

%files plugins
%defattr(-,root,root,-)
%dir %{_libdir}/qt5/plugins/calligra
%dir %{_libdir}/qt5/plugins/calligra/parts
%{_libdir}/qt5/plugins/calligra/pageapptools
%{_libdir}/qt5/plugins/calligra/textinlineobjects
%{_libdir}/qt5/plugins/calligra/tools
%dir %{_libdir}/qt5/plugins/calligra/shapes
%{_libdir}/qt5/plugins/calligra/shapes/calligra_shape_text.so
%{_libdir}/qt5/plugins/calligra/shapes/calligra_shape_picture.so
%{_libdir}/qt5/plugins/calligra/shapes/calligra_shape_chart.so
%{_libdir}/qt5/plugins/calligra/shapes/calligra_shape_paths.so

%files words-core
%defattr(-,root,root,-)
%{_libdir}/libwordsprivate.so.*
%{_libdir}/qt5/plugins/calligra/parts/calligrawordspart.so
%dir %{_datadir}/calligrawords
%{_datadir}/calligrawords/styles
%{_datadir}/icons/hicolor/256x256/apps/calligrawords.png
%{_datadir}/icons/hicolor/512x512/apps/calligrawords.png
%{_datadir}/icons/hicolor/22x22/apps/calligrawords.png
%{_datadir}/icons/hicolor/1024x1024/apps/calligrawords.png
%{_datadir}/icons/hicolor/32x32/apps/calligrawords.png
%{_datadir}/icons/hicolor/scalable/apps/calligrawords.svgz
%{_datadir}/icons/hicolor/48x48/apps/calligrawords.png
%{_datadir}/icons/hicolor/16x16/apps/calligrawords.png
%{_datadir}/icons/hicolor/64x64/apps/calligrawords.png
%{_datadir}/icons/hicolor/128x128/apps/calligrawords.png
%dir %{_datadir}/calligrawords/icons/
%dir %{_datadir}/calligrawords/icons/hicolor
%dir %{_datadir}/calligrawords/icons/hicolor/22x22
%{_datadir}/calligrawords/icons/hicolor/22x22/actions
%{_datadir}/kxmlgui5/calligrawords
%{_sysconfdir}/xdg/calligrawordsrc
%exclude %{_libdir}/libwordsprivate.so

%files words-templates
%defattr(-,root,root,-)
%{_datadir}/calligrawords/templates
%{_datadir}/calligrawords/icons/hicolor/scalable/actions/template_*.svgz
%{_datadir}/calligrawords/icons/hicolor/48x48/actions/template_*.png
%{_datadir}/calligrawords/icons/hicolor/128x128/actions/template_*.png

%files sheets-core
%defattr(-,root,root,-)
%{_libdir}/libcalligrasheetsodf.so.*
%{_libdir}/libcalligrasheetscommon.so.*
%{_libdir}/qt5/plugins/calligra/parts/calligrasheetspart.so
%{_libdir}/qt5/plugins/calligrasheets
%{_datadir}/icons/hicolor/256x256/apps/calligrasheets.png
%{_datadir}/icons/hicolor/512x512/apps/calligrasheets.png
%{_datadir}/icons/hicolor/22x22/apps/calligrasheets.png
%{_datadir}/icons/hicolor/1024x1024/apps/calligrasheets.png
%{_datadir}/icons/hicolor/32x32/apps/calligrasheets.png
%{_datadir}/icons/hicolor/scalable/apps/calligrasheets.svgz
%{_datadir}/icons/hicolor/48x48/apps/calligrasheets.png
%{_datadir}/icons/hicolor/16x16/apps/calligrasheets.png
%{_datadir}/icons/hicolor/64x64/apps/calligrasheets.png
%{_datadir}/icons/hicolor/128x128/apps/calligrasheets.png
%dir %{_datadir}/calligrasheets
%dir %{_datadir}/calligrasheets/icons
%dir %{_datadir}/calligrasheets/icons/hicolor
%dir %{_datadir}/calligrasheets/icons/hicolor/16x16
%dir %{_datadir}/calligrasheets/icons/hicolor/32x32
%dir %{_datadir}/calligrasheets/icons/hicolor/22x22
%{_datadir}/calligrasheets/icons/hicolor/16x16/actions
%{_datadir}/calligrasheets/icons/hicolor/22x22/actions
%{_datadir}/calligrasheets/icons/hicolor/32x32/actions
%{_datadir}/calligrasheets/sheetstyles
%{_datadir}/calligrasheets/functions
%{_datadir}/calligrasheets/dtd
%{_datadir}/calligrasheets/CellToolOptionWidgets.xml
%{_datadir}/config.kcfg/calligrasheets.kcfg
%{_datadir}/kxmlgui5/calligrasheets
%{_sysconfdir}/xdg/calligrasheetsrc
%exclude %{_libdir}/libcalligrasheetsodf.so
%exclude %{_libdir}/libcalligrasheetscommon.so

%files sheets-templates
%defattr(-,root,root,-)
%{_datadir}/calligrasheets/templates
%{_datadir}/calligrasheets/icons/hicolor/scalable/actions/template_*.svgz
%{_datadir}/calligrasheets/icons/hicolor/48x48/actions/template_*.png

%files stage-core
%defattr(-,root,root,-)
%{_libdir}/libcalligrastageprivate.so.*
%{_libdir}/qt5/plugins/calligra/parts/calligrastagepart.so
%{_libdir}/qt5/plugins/calligrastage
%{_datadir}/calligrastage/animations
%{_datadir}/calligrastage/cursors
%{_datadir}/calligrastage/pics
%{_datadir}/calligrastage/styles
%dir %{_datadir}/calligrastage
%dir %{_datadir}/calligrastage/icons
%dir %{_datadir}/calligrastage/icons/hicolor
%dir %{_datadir}/calligrastage/icons/hicolor/16x16
%dir %{_datadir}/calligrastage/icons/hicolor/32x32
%dir %{_datadir}/calligrastage/icons/hicolor/64x64
%{_datadir}/calligrastage/icons/hicolor/16x16/actions
%{_datadir}/calligrastage/icons/hicolor/32x32/actions
%{_datadir}/calligrastage/icons/hicolor/64x64/actions
%{_datadir}/calligrastage/icons/hicolor/scalable/actions
%{_datadir}/icons/hicolor/256x256/apps/calligrastage.png
%{_datadir}/icons/hicolor/512x512/apps/calligrastage.png
%{_datadir}/icons/hicolor/22x22/apps/calligrastage.png
%{_datadir}/icons/hicolor/1024x1024/apps/calligrastage.png
%{_datadir}/icons/hicolor/32x32/apps/calligrastage.png
%{_datadir}/icons/hicolor/scalable/apps/calligrastage.svgz
%{_datadir}/icons/hicolor/48x48/apps/calligrastage.png
%{_datadir}/icons/hicolor/16x16/apps/calligrastage.png
%{_datadir}/icons/hicolor/64x64/apps/calligrastage.png
%{_datadir}/icons/hicolor/128x128/apps/calligrastage.png
%{_datadir}/kxmlgui5/calligrastage
%{_sysconfdir}/xdg/calligrastagerc
%exclude %{_libdir}/libcalligrastageprivate.so

%files stage-templates
%defattr(-,root,root,-)
%{_datadir}/calligrastage/templates
%{_datadir}/calligrastage/icons/hicolor/scalable/actions/template_*.svgz
%{_datadir}/calligrastage/icons/hicolor/48x48/actions/template_*.png

%files kf5
%defattr(-,root,root,-)
%{_libdir}/calligra-kf5

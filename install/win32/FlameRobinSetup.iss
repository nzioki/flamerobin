; The contents of this file are subject to the Initial Developer's Public
; License Version 1.0 (the "License"); you may not use this file except in
; compliance with the License. You may obtain a copy of the License here:
; http://www.flamerobin.org/license.html.
;
; Software distributed under the License is distributed on an "AS IS"
; basis, WITHOUT WARRANTY OF ANY KIND, either express or implied. See the
; License for the specific language governing rights and limitations under
; the License.
;
; The Original Code is FlameRobin Win32 Installation Program.
;
; The Initial Developer of the Original Code is Nando Dessena.
;
; Portions created by the original developer
; are Copyright (C) 2004 Nando Dessena.
;
; All Rights Reserved.
;
; Contributor(s):

;#define DEBUG

; TODO: can we centralize this?
#define VERSION "0.3.0"

[Setup]
AppName=FlameRobin
AppVerName=FlameRobin {#VERSION} ALPHA
AppPublisher=The FlameRobin Project
AppPublisherURL=http://www.flamerobin.org
AppSupportURL=http://www.flamerobin.org
AppUpdatesURL=http://www.flamerobin.org
DefaultDirName={pf}\FlameRobin
DefaultGroupName=FlameRobin
AllowNoIcons=true
LicenseFile=..\..\docs-src\fr_license.txt
InfoAfterFile=
#ifdef DEBUG
Compression=lzma/ultra
OutputBaseFilename=flamerobin-{#VERSION}-setup-debug
#else
Compression=lzma
OutputBaseFilename=flamerobin-{#VERSION}-setup
#endif
SolidCompression=true
OutputDir=.\output
InfoBeforeFile=..\..\docs-src\fr_whatsnew.txt
InternalCompressLevel=ultra
ShowLanguageDialog=yes

[Tasks]
Name: desktopicon; Description: {cm:CreateDesktopIcon}; GroupDescription: {cm:AdditionalIcons}
Name: quicklaunchicon; Description: {cm:CreateQuickLaunchIcon}; GroupDescription: {cm:AdditionalIcons}

[Files]
#ifdef DEBUG
Source: ..\..\vcd\flamerobin.exe; DestDir: {app}; Flags: ignoreversion; MinVersion: 4.0.950,0
Source: ..\..\vcud\flamerobin.exe; DestDir: {app}; Flags: ignoreversion; MinVersion: 0,4.0.1381
#else
Source: ..\..\vc\flamerobin.exe; DestDir: {app}; Flags: ignoreversion; MinVersion: 4.0.950,0
Source: ..\..\vcu\flamerobin.exe; DestDir: {app}; Flags: ignoreversion; MinVersion: 0,4.0.1381
#endif
Source: ..\..\res\flamerobin.exe.Manifest; DestDir: {app}; Flags: ignoreversion; MinVersion: 0,5.01.2600
Source: ..\..\docs\fr_license.html; DestDir: {app}\doc; Flags: ignoreversion
Source: ..\..\docs\fr_manual.html; DestDir: {app}\doc; Flags: ignoreversion
Source: ..\..\docs\fr_whatsnew.html; DestDir: {app}\doc; Flags: ignoreversion
Source: ..\..\html-templates\*.*; DestDir: {app}\html-templates; Flags: ignoreversion
Source: ..\..\confdefs\*.*; DestDir: {app}\confdefs; Flags: ignoreversion
Source: ..\..\res\system32\msvcr71.dll; DestDir: {app}; MinVersion: 0,5.0.2195
Source: ..\..\res\system32\msvcr71.dll; DestDir: {sys}; Flags: sharedfile uninsneveruninstall; OnlyBelowVersion: 0,5.0.2195
Source: ..\..\res\system32\msvcp71.dll; DestDir: {app}; MinVersion: 0,5.0.2195
Source: ..\..\res\system32\msvcp71.dll; DestDir: {sys}; Flags: sharedfile uninsneveruninstall; OnlyBelowVersion: 0,5.0.2195

[INI]
Filename: {app}\flamerobin.url; Section: InternetShortcut; Key: URL; String: http://www.flamerobin.org

[Icons]
Name: {group}\FlameRobin; Filename: {app}\flamerobin.exe; WorkingDir: {app}
Name: {group}\License; Filename: {app}\docs\fr_license.html
Name: {group}\Manual; Filename: {app}\docs\fr_manual.html
Name: {group}\What's new; Filename: {app}\docs\fr_whatsnew.html
Name: {group}\{cm:ProgramOnTheWeb,FlameRobin}; Filename: {app}\flamerobin.url
Name: {group}\{cm:UninstallProgram,FlameRobin}; Filename: {uninstallexe}
Name: {userdesktop}\FlameRobin; Filename: {app}\flamerobin.exe; Tasks: desktopicon; WorkingDir: {app}; IconIndex: 0
Name: {userappdata}\Microsoft\Internet Explorer\Quick Launch\FlameRobin; Filename: {app}\flamerobin.exe; Tasks: quicklaunchicon; WorkingDir: {app}; IconIndex: 0

[Run]
Filename: {app}\flamerobin.exe; Description: {cm:LaunchProgram,FlameRobin}; Flags: nowait postinstall skipifsilent
Filename: {app}\docs\fr_whatsnew.html; WorkingDir: {app}\doc\; Description: Show Release Notes; StatusMsg: Showing Release notes; Flags: nowait shellexec postinstall

[UninstallDelete]
Type: files; Name: {app}\flamerobin.url

[_ISTool]
UseAbsolutePaths=false

#expr SaveToFile(AddBackslash(SourcePath) + "FlameRobinSetup_Preprocessed.iss")

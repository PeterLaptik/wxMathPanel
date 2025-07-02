# Updates BUILD_VERSION in Makefile from the root configure.ac

$str = cat .\..\..\configure.ac -First 1
$str -match '\d+\.\d+\.\d+'
$version = $Matches[0]

$content = Get-Content ".\Makefile"
$content[9] = "BUILD_VERSION = $version"
$content | Set-Content .\Makefile

$content_res = Get-Content ".\wxmathpanel.rc"
$content_res[12] = "FILEVERSION             $version.0"
$content_res[13] = "PRODUCTVERSION          $version.0"
$content_res[27] = "    	VALUE `"FileVersion`",      `"$version`""
$content_res[30] = "		VALUE `"OriginalFilename`", `"wx_mathpanel-$version.dll`""
$content_res[32] = "		VALUE `"ProductVersion`",	  `"$version`""
$content_res | Set-Content .\wxmathpanel.rc

echo Version: $version
pause
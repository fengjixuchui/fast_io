#include"../../include/fast_io.h"
#include"../../include/fast_io_legacy.h"

int main()
{
	const auto err_mode = _setmode(2, _O_U16TEXT);
	print(fast_io::wc_stderr,
		L"Supported actions are:\n"
		L"    l, list            List all installed distributions.\n"
		L"    gd, get-default    Get the default distribution, which is used by bash.exe.\n"
		L"    sd, set-default    Set the default distribution, which is used by bash.exe.\n"
		L"    i, install         Install a new distribution.\n"
		L"    ui, uninstall      Uninstall a distribution.\n"
		L"    rg, register       Register an existing installation directory.\n"
		L"    ur, unregister     Unregister a distribution but not delete the installation directory.\n"
		L"    m, move            Move a distribution to a new directory.\n"
		L"    d, duplicate       Duplicate an existing distribution in a new directory.\n"
		L"    e, export          Export a distribution's filesystem to a .tar.gz file, which can be imported by the \"install\" command.\n"
		L"    r, run             Run a command in a distribution.\n"
		L"    di, get-dir        Get the installation directory of a distribution.\n"
		L"    gv, get-version    Get the filesystem version of a distribution.\n"
		L"    ge, get-env        Get the default environment variables of a distribution.\n"
		L"    se, set-env        Set the default environment variables of a distribution.\n"
		L"    ae, add-env        Add to the default environment variables of a distribution.\n"
		L"    re, remove-env     Remove from the default environment variables of a distribution.\n"
		L"    gu, get-uid        Get the UID of the default user of a distribution.\n"
		L"    su, set-uid        Set the UID of the default user of a distribution.\n"
		L"    gk, get-kernelcmd  Get the default kernel command line of a distribution.\n"
		L"    sk, set-kernelcmd  Set the default kernel command line of a distribution.\n"
		L"    gf, get-flags      Get some flags of a distribution. See https://docs.microsoft.com/en-us/previous-versions/windows/desktop/api/wslapi/ne-wslapi-wsl_distribution_flags for details.\n"
		L"    sf, set-flags      Set some flags of a distribution. See https://docs.microsoft.com/en-us/previous-versions/windows/desktop/api/wslapi/ne-wslapi-wsl_distribution_flags for details.\n"
		L"    s, shortcut        Create a shortcut to launch a distribution.\n"
		L"    ec, export-config  Export configuration of a distribution to an XML file.\n"
		L"    ic, import-config  Import configuration of a distribution from an XML file.\n"
		L"    sm, summary        Get general information of a distribution.\n"
		L"    version            Get version information about this LxRunOffline.exe.\n"
	);
}
# vc-string-bug

This is a reproduction case for a bug described in this issue:

https://developercommunity.visualstudio.com/t/ABI-compatibility-issues-for-std::string/10199519

The problem is that VC++ libraries built in GitHub actions with
VC++ toolset 14.33 generate code that does not interact properly
with applications built with VC++ toolset 14.34 in that libraries
construct `std::string` instances that are not null-terminated.

The intent for this repository is to build a library on a GitHub
runner and link it against an application built with the current
version of VC++.

**NOTE**: GitHub updated its runners with VC++ toolset 14.34,
so this issue is no longer reproducible, as described.

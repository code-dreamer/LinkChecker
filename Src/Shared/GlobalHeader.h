#pragma once

#if ( defined(WIN64) || defined(_WIN64) || defined(__WIN64) )
#	error "_WIN64 was defined"
#endif

#ifndef _CPPRTTI
#	error "Run-Time Type Information must be enabled"
#endif

#include "Shared/TargetWinVersion.h"
#include "Shared/Defines.h"
#include "Shared/SharedTools.h"
#include "Shared/SolutionShared.h"

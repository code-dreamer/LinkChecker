#pragma once

enum class LogLevel
{
	debug		=	0x0		// Debug messages. Can be useful for app debugging
							// "Point x pos changed to 104"

	, info		=	0x1		// Information messages. Can be useful for signaling about important events in application.
							// This information can be interesting for administrators too.
							// "'Quake 2' game downloading started"

	, warning	=	0x2		// Can be useful if some strange, but non-fatal has happen
							// "Partial allocation for 'Quake 2' failed. Prepare for full allocation..."

	, error		=	0x4		// Error (not critical). Application may remain unstable but not crashing.
							// "Can't load icon 'smile.png'. Windows error 2."

	, critical	=	0x8		// Critical error. Some application components may not work correctly.
							// "Can't communicate with database. All data operations will be disabled"

	, fatal		=	0x10	// Fatal, unrecoverable error. Application in crash state and can't be recovered (unhandled exceptions handlers and etc).
							// "Unhanded Exception. Code 0xC0000005 (access violation). Address:
};

static QString levelToStr(LogLevel level)
{
	switch (level) {
	case LogLevel::debug:
		return QLatin1String("Debug");
	case LogLevel::info:
		return QLatin1String("Info");
	case LogLevel::warning:
		return QLatin1String("Warning");
	case LogLevel::error:
		return QLatin1String("Error");
	case LogLevel::critical:
		return QLatin1String("Critical");
	case LogLevel::fatal:
		return QLatin1String("Fatal");
	default:
		Q_ASSERT(false);
	}

	return QString();
}
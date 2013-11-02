#pragma once

#define debug(...) do { if (getenv("DEBUG")) { __VA_ARGS__ ; } } while (0)

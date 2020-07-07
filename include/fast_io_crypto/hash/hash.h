#pragma once

#include"hash_processor.h"
#include"jenkins.h"
#include"crc.h"
#include"md5.h"
#include"sha.h"
#include"hmac.h"
#if defined(__GNUC__)
#include"poly1305.h"
#endif
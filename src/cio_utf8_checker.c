// Copyright (c) 2008-2010 Bjoern Hoehrmann <bjoern@hoehrmann.de>
// See http://bjoern.hoehrmann.de/utf-8/decoder/dfa/ for details.

#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "cio_utf8_checker.h"

static const uint8_t utf8d[] = {
    // The first part of the table maps bytes to character classes that
    // to reduce the size of the transition table and create bitmasks.
    CIO_UTF8_ACCEPT,
    CIO_UTF8_ACCEPT,
    CIO_UTF8_ACCEPT,
    CIO_UTF8_ACCEPT,
    CIO_UTF8_ACCEPT,
    CIO_UTF8_ACCEPT,
    CIO_UTF8_ACCEPT,
    CIO_UTF8_ACCEPT,
    CIO_UTF8_ACCEPT,
    CIO_UTF8_ACCEPT,
    CIO_UTF8_ACCEPT,
    CIO_UTF8_ACCEPT,
    CIO_UTF8_ACCEPT,
    CIO_UTF8_ACCEPT,
    CIO_UTF8_ACCEPT,
    CIO_UTF8_ACCEPT,
    CIO_UTF8_ACCEPT,
    CIO_UTF8_ACCEPT,
    CIO_UTF8_ACCEPT,
    CIO_UTF8_ACCEPT,
    CIO_UTF8_ACCEPT,
    CIO_UTF8_ACCEPT,
    CIO_UTF8_ACCEPT,
    CIO_UTF8_ACCEPT,
    CIO_UTF8_ACCEPT,
    CIO_UTF8_ACCEPT,
    CIO_UTF8_ACCEPT,
    CIO_UTF8_ACCEPT,
    CIO_UTF8_ACCEPT,
    CIO_UTF8_ACCEPT,
    CIO_UTF8_ACCEPT,
    CIO_UTF8_ACCEPT,
    CIO_UTF8_ACCEPT,
    CIO_UTF8_ACCEPT,
    CIO_UTF8_ACCEPT,
    CIO_UTF8_ACCEPT,
    CIO_UTF8_ACCEPT,
    CIO_UTF8_ACCEPT,
    CIO_UTF8_ACCEPT,
    CIO_UTF8_ACCEPT,
    CIO_UTF8_ACCEPT,
    CIO_UTF8_ACCEPT,
    CIO_UTF8_ACCEPT,
    CIO_UTF8_ACCEPT,
    CIO_UTF8_ACCEPT,
    CIO_UTF8_ACCEPT,
    CIO_UTF8_ACCEPT,
    CIO_UTF8_ACCEPT,
    CIO_UTF8_ACCEPT,
    CIO_UTF8_ACCEPT,
    CIO_UTF8_ACCEPT,
    CIO_UTF8_ACCEPT,
    CIO_UTF8_ACCEPT,
    CIO_UTF8_ACCEPT,
    CIO_UTF8_ACCEPT,
    CIO_UTF8_ACCEPT,
    CIO_UTF8_ACCEPT,
    CIO_UTF8_ACCEPT,
    CIO_UTF8_ACCEPT,
    CIO_UTF8_ACCEPT,
    CIO_UTF8_ACCEPT,
    CIO_UTF8_ACCEPT,
    CIO_UTF8_ACCEPT,
    CIO_UTF8_ACCEPT,
    CIO_UTF8_ACCEPT,
    CIO_UTF8_ACCEPT,
    CIO_UTF8_ACCEPT,
    CIO_UTF8_ACCEPT,
    CIO_UTF8_ACCEPT,
    CIO_UTF8_ACCEPT,
    CIO_UTF8_ACCEPT,
    CIO_UTF8_ACCEPT,
    CIO_UTF8_ACCEPT,
    CIO_UTF8_ACCEPT,
    CIO_UTF8_ACCEPT,
    CIO_UTF8_ACCEPT,
    CIO_UTF8_ACCEPT,
    CIO_UTF8_ACCEPT,
    CIO_UTF8_ACCEPT,
    CIO_UTF8_ACCEPT,
    CIO_UTF8_ACCEPT,
    CIO_UTF8_ACCEPT,
    CIO_UTF8_ACCEPT,
    CIO_UTF8_ACCEPT,
    CIO_UTF8_ACCEPT,
    CIO_UTF8_ACCEPT,
    CIO_UTF8_ACCEPT,
    CIO_UTF8_ACCEPT,
    CIO_UTF8_ACCEPT,
    CIO_UTF8_ACCEPT,
    CIO_UTF8_ACCEPT,
    CIO_UTF8_ACCEPT,
    CIO_UTF8_ACCEPT,
    CIO_UTF8_ACCEPT,
    CIO_UTF8_ACCEPT,
    CIO_UTF8_ACCEPT,
    CIO_UTF8_ACCEPT,
    CIO_UTF8_ACCEPT,
    CIO_UTF8_ACCEPT,
    CIO_UTF8_ACCEPT,
    CIO_UTF8_ACCEPT,
    CIO_UTF8_ACCEPT,
    CIO_UTF8_ACCEPT,
    CIO_UTF8_ACCEPT,
    CIO_UTF8_ACCEPT,
    CIO_UTF8_ACCEPT,
    CIO_UTF8_ACCEPT,
    CIO_UTF8_ACCEPT,
    CIO_UTF8_ACCEPT,
    CIO_UTF8_ACCEPT,
    CIO_UTF8_ACCEPT,
    CIO_UTF8_ACCEPT,
    CIO_UTF8_ACCEPT,
    CIO_UTF8_ACCEPT,
    CIO_UTF8_ACCEPT,
    CIO_UTF8_ACCEPT,
    CIO_UTF8_ACCEPT,
    CIO_UTF8_ACCEPT,
    CIO_UTF8_ACCEPT,
    CIO_UTF8_ACCEPT,
    CIO_UTF8_ACCEPT,
    CIO_UTF8_ACCEPT,
    CIO_UTF8_ACCEPT,
    CIO_UTF8_ACCEPT,
    CIO_UTF8_ACCEPT,
    CIO_UTF8_ACCEPT,
    CIO_UTF8_ACCEPT,
    CIO_UTF8_ACCEPT,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    9,
    9,
    9,
    9,
    9,
    9,
    9,
    9,
    9,
    9,
    9,
    9,
    9,
    9,
    9,
    9,
    7,
    7,
    7,
    7,
    7,
    7,
    7,
    7,
    7,
    7,
    7,
    7,
    7,
    7,
    7,
    7,
    7,
    7,
    7,
    7,
    7,
    7,
    7,
    7,
    7,
    7,
    7,
    7,
    7,
    7,
    7,
    7,
    8,
    8,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    10,
    3,
    3,
    3,
    3,
    3,
    3,
    3,
    3,
    3,
    3,
    3,
    3,
    4,
    3,
    3,
    11,
    6,
    6,
    6,
    5,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,

    // The second part is a transition table that maps a combination
    // of a state of the automaton and a character class to a state.
    CIO_UTF8_ACCEPT,
    CIO_UTF8_REJECT,
    24,
    36,
    60,
    96,
    84,
    CIO_UTF8_REJECT,
    CIO_UTF8_REJECT,
    CIO_UTF8_REJECT,
    48,
    72,
    CIO_UTF8_REJECT,
    CIO_UTF8_REJECT,
    CIO_UTF8_REJECT,
    CIO_UTF8_REJECT,
    CIO_UTF8_REJECT,
    CIO_UTF8_REJECT,
    CIO_UTF8_REJECT,
    CIO_UTF8_REJECT,
    CIO_UTF8_REJECT,
    CIO_UTF8_REJECT,
    CIO_UTF8_REJECT,
    CIO_UTF8_REJECT,
    CIO_UTF8_REJECT,
    CIO_UTF8_ACCEPT,
    CIO_UTF8_REJECT,
    CIO_UTF8_REJECT,
    CIO_UTF8_REJECT,
    CIO_UTF8_REJECT,
    CIO_UTF8_REJECT,
    CIO_UTF8_ACCEPT,
    CIO_UTF8_REJECT,
    CIO_UTF8_ACCEPT,
    CIO_UTF8_REJECT,
    CIO_UTF8_REJECT,
    CIO_UTF8_REJECT,
    24,
    CIO_UTF8_REJECT,
    CIO_UTF8_REJECT,
    CIO_UTF8_REJECT,
    CIO_UTF8_REJECT,
    CIO_UTF8_REJECT,
    24,
    CIO_UTF8_REJECT,
    24,
    CIO_UTF8_REJECT,
    CIO_UTF8_REJECT,
    CIO_UTF8_REJECT,
    CIO_UTF8_REJECT,
    CIO_UTF8_REJECT,
    CIO_UTF8_REJECT,
    CIO_UTF8_REJECT,
    CIO_UTF8_REJECT,
    CIO_UTF8_REJECT,
    24,
    CIO_UTF8_REJECT,
    CIO_UTF8_REJECT,
    CIO_UTF8_REJECT,
    CIO_UTF8_REJECT,
    CIO_UTF8_REJECT,
    24,
    CIO_UTF8_REJECT,
    CIO_UTF8_REJECT,
    CIO_UTF8_REJECT,
    CIO_UTF8_REJECT,
    CIO_UTF8_REJECT,
    CIO_UTF8_REJECT,
    CIO_UTF8_REJECT,
    24,
    CIO_UTF8_REJECT,
    CIO_UTF8_REJECT,
    CIO_UTF8_REJECT,
    CIO_UTF8_REJECT,
    CIO_UTF8_REJECT,
    CIO_UTF8_REJECT,
    CIO_UTF8_REJECT,
    CIO_UTF8_REJECT,
    CIO_UTF8_REJECT,
    36,
    CIO_UTF8_REJECT,
    36,
    CIO_UTF8_REJECT,
    CIO_UTF8_REJECT,
    CIO_UTF8_REJECT,
    36,
    CIO_UTF8_REJECT,
    CIO_UTF8_REJECT,
    CIO_UTF8_REJECT,
    CIO_UTF8_REJECT,
    CIO_UTF8_REJECT,
    36,
    CIO_UTF8_REJECT,
    36,
    CIO_UTF8_REJECT,
    CIO_UTF8_REJECT,
    CIO_UTF8_REJECT,
    36,
    CIO_UTF8_REJECT,
    CIO_UTF8_REJECT,
    CIO_UTF8_REJECT,
    CIO_UTF8_REJECT,
    CIO_UTF8_REJECT,
    CIO_UTF8_REJECT,
    CIO_UTF8_REJECT,
    CIO_UTF8_REJECT,
    CIO_UTF8_REJECT,
    CIO_UTF8_REJECT,
};

static const uint8_t type_mask = 0x3fU;
static const uint8_t shift = 6U;
static const uint8_t byte_mask = 0xffU;
static const unsigned int next_byte = 256U;

static inline uint8_t decode(uint8_t *state, uint8_t *codep, uint8_t byte)
{
	uint8_t type = utf8d[byte];

	*codep = (uint8_t)((*state != CIO_UTF8_ACCEPT) ? ((uint8_t)(byte & type_mask) | (uint8_t)(*codep << shift)) : ((uint8_t)(byte_mask >> type) & byte));

	*state = utf8d[next_byte + *state + type];
	return *state;
}

uint8_t cio_check_utf8(struct cio_utf8_state *state, const uint8_t *s, size_t count)
{
	const uint_fast32_t *s_aligned;
	unsigned int pre_length;
	size_t main_length;
	unsigned int post_length;

	if (count < sizeof(*s_aligned)) {
		pre_length = (unsigned int)count;
		main_length = 0;
		post_length = 0;
	} else {
		pre_length = ((uintptr_t)s) % sizeof(*s_aligned);
		pre_length = (sizeof(*s_aligned) - pre_length) % sizeof(*s_aligned);
		main_length = (count - pre_length) / sizeof(*s_aligned);
		post_length = (unsigned int)(count - pre_length - (main_length * sizeof(*s_aligned)));
	}

	s_aligned = (const void *)(s + pre_length);

	size_t i_p = 0;
	while (pre_length > 0) {
		if (decode(&state->state, &state->codepoint, s[i_p]) == CIO_UTF8_REJECT) {
			return CIO_UTF8_REJECT;
		}

		pre_length--;
		i_p++;
	}

	while (main_length-- > 0) {
		uint8_t buffer[sizeof(uint_fast32_t)];
		memcpy(buffer, s_aligned, sizeof(buffer));
		s_aligned++;
		for (uint_fast8_t i = 0; i < (uint_fast8_t)sizeof(buffer); i++) {
			uint8_t character = buffer[i];
			if (decode(&state->state, &state->codepoint, character) == CIO_UTF8_REJECT) {
				return CIO_UTF8_REJECT;
			}
		}
	}

	i_p = count - post_length;
	while (post_length > 0) {
		if (decode(&state->state, &state->codepoint, s[i_p]) == CIO_UTF8_REJECT) {
			return CIO_UTF8_REJECT;
		}

		post_length--;
		i_p++;
	}

	return state->state;
}

void cio_utf8_init(struct cio_utf8_state *state)
{
	state->state = 0;
}

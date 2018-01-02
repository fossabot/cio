/*
 * The MIT License (MIT)
 *
 * Copyright (c) <2014> <Stephan Gatzka>
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

function compareVersions(actualVersionParts, expectedVersionParts) {
    var i;
    for (i = 0; i < expectedVersionParts.length; ++i) {
        if (actualVersionParts[i] > expectedVersionParts[i]) {
            return true;
        } else if (actualVersionParts[i] < expectedVersionParts[i]) {
            return false;
        }
    }

    return (i === expectedVersionParts.length) || (expectedVersionParts[i] === 0);
}

function versionIsAtLeast(actualVersion, expectedVersion) {
    var actualVersionParts = actualVersion.split(".").map(function(item) {
        return parseInt(item, 10);
    });
    var expectedVersionParts = expectedVersion.split(".").map(function(item) {
        return parseInt(item, 10);
    });

	return compareVersions(actualVersionParts, expectedVersionParts);
}

// The MIT License (MIT)

// Copyright (c) 2016, Microsoft

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#pragma once

#include <atomic>   // std::atomic member
#include <iosfwd>   // std::ostream parameter
#include <map>      // std::map member
#include <mutex>    // std::mutex member

#include "BitFunnel/NonCopyable.h"


// BitFunnelLib\src\Common\Configuration\DocumentDocumentLengthHistogram.cpp
// TODO: one unit test should be to write and read and get the same result.
// Another should be to put some known stuff in and count it correctly.

namespace BitFunnel
{
    class DocumentHistogramBuilder : public NonCopyable
    {
    public:
        DocumentHistogramBuilder();

        // AddDocument is thread safe with multiple writers.
        void AddDocument(size_t postingCount);

        size_t GetPostingCount() const;

        // GetValue is thread safe with multiple readers and writers.
        size_t GetValue(size_t postingCount) const;

        // Persists the contents of the histogram to a stream, not thread-safe
        void Write(std::ostream& output) const;


    private:
        std::map<size_t, size_t> m_hist;
        mutable std::mutex m_lock;

        std::atomic<size_t> m_totalCount;
    };
}

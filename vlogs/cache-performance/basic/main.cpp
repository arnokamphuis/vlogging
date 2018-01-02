#include <benchmark/benchmark.h>
#include <iostream>
#include <vector>

#include "rnd.h"

using datatype = int32_t;

static void cacheBench(benchmark::State& s) {
    int64_t bytes = 1 << s.range(0);
    int64_t count = (bytes/ sizeof(datatype))/2;

    std::vector<datatype> v;
    v.reserve(count);
    for (auto i: RND<datatype>(std::numeric_limits<datatype>::min(), std::numeric_limits<datatype>::max(), count))
        v.push_back(i);
    
    std::vector<datatype> ind;
    ind.reserve(count);
    for (auto i: RND<datatype>(0, count, count))
        ind.push_back(i);

    for (auto _ : s) {
        int64_t sum = 0;
        for (datatype i: ind) sum += v[i];
        benchmark::DoNotOptimize(sum);
    }

    s.SetBytesProcessed(int64_t(s.iterations()) * bytes);
    s.SetLabel(std::to_string(bytes/1024) + "kb");
}
BENCHMARK(cacheBench)->DenseRange(10,23)->Repetitions(20)->ReportAggregatesOnly(true);

BENCHMARK_MAIN();
#include <benchmark/benchmark.h>
#include <vector>

#include "rnd.h"

static void cacheBench(benchmark::State& s) {
    int bytes = 1 << s.range(0);
    int count = (bytes/ sizeof(int))/2;

    std::vector<int> v;
    v.reserve(count);
    for (auto i: RND<int>(std::numeric_limits<int>::min(), std::numeric_limits<int>::max(), count))
        v.push_back(i);
    
    std::vector<int> ind;
    ind.reserve(count);
    for (auto i: RND<int>(0, count, count))
        ind.push_back(i);

    while (s.KeepRunning()) {
        long sum = 0;
        for (int i: ind)
            sum += v[i];
        benchmark::DoNotOptimize(sum);
    }

    s.SetBytesProcessed(long(s.iterations()) * long(bytes));
    s.SetLabel(std::to_string(bytes/1024)+"kb");
}
BENCHMARK(cacheBench)->DenseRange(11,23)->ReportAggregatesOnly(true);

BENCHMARK_MAIN();
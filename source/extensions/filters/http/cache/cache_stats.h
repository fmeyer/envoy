#pragma once

#include <memory>
#include <string>
#include <vector>

#include "envoy/stats/scope.h"

#include "common/stats/symbol_table_impl.h"
#include "common/stats/utility.h"

namespace Envoy {
namespace Extensions {
namespace HttpFilters {
namespace Cache {

class CacheStats {
public:
  CacheStats(Stats::Scope& scope, absl::string_view prefix,
             const std::vector<std::string>& commands);

  void incCounter(const Stats::ElementVec& names);
  void recordHistogram(const Stats::ElementVec& names, Stats::Histogram::Unit unit,
                       uint64_t sample);

  Stats::StatName getBuiltin(const std::string& str, Stats::StatName fallback) {
    return stat_name_set_->getBuiltin(str, fallback);
  }

private:
  Stats::ElementVec addPrefix(const Stats::ElementVec& names);

  Stats::Scope& scope_;
  Stats::StatNameSetPtr stat_name_set_;
  const Stats::StatName prefix_;  

public:
  const Stats::StatName capacity_; 
  const Stats::StatName hit_; 
  const Stats::StatName miss_; 
  const Stats::StatName evicted_;
  const Stats::StatName effectiveness_;
  const Stats::StatName current_; 
  const Stats::StatName max_; 

};
using CacheStatsSharedPtr = std::shared_ptr<CacheStats>;

} // namespace Cache
} // namespace HttpFilters
} // namespace Extensions
} // namespace Envoy

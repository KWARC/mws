/*

Copyright (C) 2010-2013 KWARC Group <kwarc.info>

This file is part of MathWebSearch.

MathWebSearch is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

MathWebSearch is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with MathWebSearch.  If not, see <http://www.gnu.org/licenses/>.

*/
#ifndef _MWS_PARSER_PROCESSMWSHARVEST_HPP
#define _MWS_PARSER_PROCESSMWSHARVEST_HPP

/**
  * @file processMwsHarvest.hpp
  * @author Corneliu-Claudiu Prodescu
  * @date 30 Apr 2011
  *
  * @edited Radu Hambasan
  * @date 04 May 2014
  * License: GPL v3
  *
  */

#include <stdint.h>

#include <string>
#include <vector>
#include <map>
#include <utility>

#include "mws/types/CmmlToken.hpp"
#include "mws/dbc/CrawlDb.hpp"
#include "common/utils/Path.hpp"

namespace mws {
namespace parser {

class HarvestProcessor {
 public:
    /**
     * crawlId might be CRAWLID_NULL if there was no data associated
     * with the expression, or processData() did not return a crawlId
     * @brief called when an expr element has been parsed
     * @param expression CmmlToken corresponding to the parsed expr
     * @param exprUri
     * @param crawlId of data associated with this expression
     * @return 0 if expr was processed successfully, different otherwise
     */
    virtual int processExpression(const types::CmmlToken* expression,
                                  const std::string& exprUri,
                                  const uint32_t& crawlId) = 0;
    /**
     * @brief called when a data element has been parsed
     * @param data contained in the data element
     * @return a CrawlId, if the expressions are linked with data,
     * CRAWLID_NULL otherwise
     */
    virtual dbc::CrawlId processData(const std::string& data) = 0;

    virtual ~HarvestProcessor() {}
};

struct HarvestResult {
    int status;
    uint64_t numExpressions;
};

HarvestResult processHarvestFromFd(int fd, HarvestProcessor* harvestProcessor,
                                   bool shouldProcessData = true);

}  // namespace parser
}  // namespace mws

#endif  // _MWS_PARSER_PROCESSMWSHARVEST_HPP

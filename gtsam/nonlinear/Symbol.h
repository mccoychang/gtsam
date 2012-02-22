/* ----------------------------------------------------------------------------

 * GTSAM Copyright 2010, Georgia Tech Research Corporation, 
 * Atlanta, Georgia 30332-0415
 * All Rights Reserved
 * Authors: Frank Dellaert, et al. (see THANKS for the full author list)

 * See LICENSE for the license information

 * -------------------------------------------------------------------------- */

/**
 * @file Symbol.h
 * @date Jan 12, 2010
 * @author: Frank Dellaert
 * @author: Richard Roberts
 */

#pragma once

#include <list>
#include <iostream>
#include <boost/mpl/char.hpp>
#include <boost/format.hpp>
#include <boost/serialization/nvp.hpp>

#include <gtsam/nonlinear/Key.h>

namespace gtsam {

/**
 * Character and index key used in VectorValues, GaussianFactorGraph,
 * GaussianFactor, etc.  These keys are generated at runtime from TypedSymbol
 * keys when linearizing a nonlinear factor graph.  This key is not type
 * safe, so cannot be used with any Nonlinear* classes.
 */
class Symbol {
protected:
  unsigned char c_;
  size_t j_;

public:
  /** Default constructor */
  Symbol() :
    c_(0), j_(0) {
  }

  /** Copy constructor */
  Symbol(const Symbol& key) :
    c_(key.c_), j_(key.j_) {
  }

  /** Constructor */
  Symbol(unsigned char c, size_t j) :
    c_(c), j_(j) {
  }

  /** Constructor that decodes an integer Key */
  Symbol(Key key) {
    const size_t keyBytes = sizeof(Key);
    const size_t chrBytes = sizeof(unsigned char);
    const size_t indexBytes = keyBytes - chrBytes;
    const Key chrMask = std::numeric_limits<unsigned char>::max() << indexBytes;
    const Key indexMask = ~chrMask;
    c_ = (key & chrMask) >> indexBytes;
    j_ = key & indexMask;
  }

  /** Cast to integer */
  operator Key() const {
    const size_t keyBytes = sizeof(Key);
    const size_t chrBytes = sizeof(unsigned char);
    const size_t indexBytes = keyBytes - chrBytes;
    const Key chrMask = std::numeric_limits<unsigned char>::max() << indexBytes;
    const Key indexMask = ~chrMask;
    if(j_ > indexMask)
      throw std::invalid_argument("Symbol index is too large");
    Key key = (c_ << indexBytes) | j_;
    return key;
  }

  // Testable Requirements
  void print(const std::string& s = "") const {
    std::cout << s << ": " << (std::string) (*this) << std::endl;
  }
  bool equals(const Symbol& expected, double tol = 0.0) const {
    return (*this) == expected;
  }

  /** Retrieve key character */
  unsigned char chr() const {
    return c_;
  }

  /** Retrieve key index */
  size_t index() const {
    return j_;
  }

  /** Create a string from the key */
  operator std::string() const {
    return str(boost::format("%c%d") % c_ % j_);
  }

  /** Comparison for use in maps */
  bool operator<(const Symbol& comp) const {
    return c_ < comp.c_ || (comp.c_ == c_ && j_ < comp.j_);
  }
  bool operator==(const Symbol& comp) const {
    return comp.c_ == c_ && comp.j_ == j_;
  }
  bool operator!=(const Symbol& comp) const {
    return comp.c_ != c_ || comp.j_ != j_;
  }

private:

  /** Serialization function */
  friend class boost::serialization::access;
  template<class ARCHIVE>
  void serialize(ARCHIVE & ar, const unsigned int version) {
    ar & BOOST_SERIALIZATION_NVP(c_);
    ar & BOOST_SERIALIZATION_NVP(j_);
  }
};

} // namespace gtsam


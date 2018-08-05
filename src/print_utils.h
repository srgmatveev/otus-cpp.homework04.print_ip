//
// Created by sergio on 01.08.18.
//
/** @file print_utils.h*/

#pragma once


#include <iosfwd>
#include <tuple>
#include <ostream>
#include <iterator>
/**
  * @addtogroup print_tuple
  * @{
  */
/**
 * @brief structure for size_t in print_tuple
 */
template<size_t> struct int_{};
/**
 * @brief print tuple variadic
 * @tparam Tuple
 * @tparam Pos - tuple member index
 * @param out - std::ostream&
 * @param t - tuple
 * @return std::ostream&
 */
template <class Tuple, size_t Pos>
std::ostream& print_tuple(std::ostream& out, const Tuple& t, int_<Pos> ) {
    out << std::get< std::tuple_size<Tuple>::value-Pos >(t) << '.';
    return print_tuple(out, t, int_<Pos-1>());
}
/**
 * @brief print tuple end recursion for print tuple variadic
 * @tparam Tuple
 * @param out - std::ostream&
 * @param t - tuple
 * @return - std::ostream&
 */
template <class Tuple>
std::ostream& print_tuple(std::ostream& out, const Tuple& t, int_<1> ) {
    return out << std::get<std::tuple_size<Tuple>::value-1>(t);
}
/**
 * @brief overload std::ostream& operator<< for tuple
 * @tparam Ts - tuple params
 * @param out - std::ostream&
 * @param tuple
 * @return - std::ostream&
 */
template <typename... Ts>
std::ostream& operator<<(std::ostream &out, const std::tuple<Ts...> &tuple){

    print_tuple(out,tuple, int_<sizeof...(Ts)>());
    return out;
}
// @} group print_tuple

//!!!next all copy from gcc stream_iterator.h and simple modified like infix_iterator!!!
/**
  * @addtogroup iterators
  * @{
  */

/// Provides input iterator semantics for streams.
template<typename _Tp, typename _CharT = char,
        typename _Traits = std::char_traits<_CharT>, typename _Dist = std::ptrdiff_t>
class istream_iterator
: public std::iterator<std::input_iterator_tag, _Tp, _Dist, const _Tp*, const _Tp&>
{
public:
    /// delemiter symbol
    typedef _CharT                         char_type;
    /// Traits type
    typedef _Traits                        traits_type;
    /// istream type
    typedef std::basic_istream<_CharT, _Traits> istream_type;

private:
    istream_type*	_M_stream;
    _Tp		_M_value;
    bool		_M_ok;

public:
    ///  Construct end of input stream iterator.
     istream_iterator()
            : _M_stream(0), _M_value(), _M_ok(false) {}

    ///  Construct start of input stream iterator.
    istream_iterator(istream_type& __s)
            : _M_stream(&__s)
    { _M_read(); }
    /// copy constructor
    /// \param __obj
    istream_iterator(const istream_iterator& __obj)
            : _M_stream(__obj._M_stream), _M_value(__obj._M_value),
              _M_ok(__obj._M_ok)
    { }
    /// Returns a reference to the element pointed to by the iterator.
    const _Tp&
    operator*() const
    {
        return _M_value;
    }
    /// The member access operator
    /// \return
    const _Tp*
    operator->() const { return &(operator*()); }
    ///Prefix increment operator.
    istream_iterator&
    operator++()
    {
        _M_read();
        return *this;
    }
    /// Postfix increment operator.
    istream_iterator
    operator++(int)
    {
        istream_iterator __tmp = *this;
        _M_read();
        return __tmp;
    }
   /**
    * @brief compare this and another class instance
    * @param __x - class instance
    * @return
    */
    bool
    _M_equal(const istream_iterator& __x) const
    { return (_M_ok == __x._M_ok) && (!_M_ok || _M_stream == __x._M_stream); }

private:
    void
    _M_read()
    {
        _M_ok = (_M_stream && *_M_stream) ? true : false;
        if (_M_ok)
        {
            *_M_stream >> _M_value;
            _M_ok = *_M_stream ? true : false;
        }
    }
};

///  Return true if x and y are both end or not end, or x and y are the same.
template<typename _Tp, typename _CharT, typename _Traits, typename _Dist>
inline bool
operator==(const istream_iterator<_Tp, _CharT, _Traits, _Dist>& __x,
           const istream_iterator<_Tp, _CharT, _Traits, _Dist>& __y)
{ return __x._M_equal(__y); }

///  Return false if x and y are both end or not end, or x and y are the same.
template <class _Tp, class _CharT, class _Traits, class _Dist>
inline bool
operator!=(const istream_iterator<_Tp, _CharT, _Traits, _Dist>& __x,
           const istream_iterator<_Tp, _CharT, _Traits, _Dist>& __y)
{ return !__x._M_equal(__y); }

/**
 *  @brief  Provides output iterator semantics for streams.
 *
 *  This class provides an iterator to write to an ostream.  The type Tp is
 *  the only type written by this iterator and there must be an
 *  operator<<(Tp) defined.
 *
 *  @tparam  _Tp  The type to write to the ostream.
 *  @tparam  _CharT  The ostream char_type.
 *  @tparam  _Traits  The ostream char_traits.
*/
template<typename _Tp, typename _CharT = char,
        typename _Traits = std::char_traits<_CharT> >
class fix_ostream_iterator
: public std::iterator<std::output_iterator_tag, void, void, void, void>
{
public:
    //@{
    /// Public typedef
    typedef _CharT                         char_type;
    typedef _Traits                        traits_type;
    typedef std::basic_ostream<_CharT, _Traits> ostream_type;
    //@}

private:
    ostream_type*	_M_stream;
    const _CharT*	_M_string;
    bool _First_element;
public:
    /// Construct from an ostream.
    fix_ostream_iterator(ostream_type& __s) : _M_stream(&__s), _M_string(0), _First_element(true) {}

    /**
     *  Construct from an ostream.
     *
     *  The delimiter string @a c is written to the stream after every Tp
     *  written to the stream.  The delimiter is not copied, and thus must
     *  not be destroyed while this iterator is in use.
     *
     *  @param  __s  Underlying ostream to write to.
     *  @param  __c  CharT delimiter string to insert.
    */
    fix_ostream_iterator(ostream_type& __s, const _CharT* __c)
            : _M_stream(&__s), _M_string(__c), _First_element(true)  { }

    /// Copy constructor.
    fix_ostream_iterator(const fix_ostream_iterator& __obj)
            : _M_stream(__obj._M_stream), _M_string(__obj._M_string), _First_element(__obj._First_element)  { }

    /// Writes @a value to underlying ostream using operator<<.  If
    /// constructed with delimiter string, writes delimiter to ostream.
    fix_ostream_iterator&
    operator=(const _Tp& __value)
    {
        if (_M_string and !_First_element) *_M_stream << _M_string;
        _First_element = false;
        *_M_stream << __value;

        return *this;
    }

    /// Returns a reference to the element pointed to by the iterator.
    fix_ostream_iterator&
    operator*()
    { return *this; }

    ///Prefix increment operator.
    fix_ostream_iterator&
    operator++()
    { return *this; }

    ///Postfix increment operator
    fix_ostream_iterator&
    operator++(int)
    { return *this; }
};

// @} group iterators
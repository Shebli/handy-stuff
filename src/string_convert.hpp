/**
 * @file handy::string_convert.hpp
 * @date Dec 13, 2018
 * @author anvar
 * @note
 * SVN tag: $Id$
 *
 * Contributors: Shebli Anvar (shebli.anvar@cea.fr)
 *
 * This software is part of the RTOS and Multitasking Programming Course.
 *
 * @copyright © Shebli Anvar, Commissariat a l'Energie Atomique et aux Energies Alternatives (CEA)
 *
 * @par FREE SOFTWARE LICENCING
 * This software is governed by the CeCILL license under French law and abiding  * by the rules of distribution of free
 * software. You can use, modify and/or redistribute the software under the terms of the CeCILL license as circulated by
 * CEA, CNRS and INRIA at the following URL: "http://www.cecill.info". As a counterpart to the access to the source code
 * and rights to copy, modify and redistribute granted by the license, users are provided only with a limited warranty
 * and the software's author, the holder of the economic rights, and the successive licensors have only limited
 * liability. In this respect, the user's attention is drawn to the risks associated with loading, using, modifying
 * and/or developing or reproducing the software by the user in light of its specific status of free software, that may
 * mean that it is complicated to manipulate, and that also therefore means that it is reserved for developers and
 * experienced professionals having in-depth computer knowledge. Users are therefore encouraged to load and test the
 * software's suitability as regards their requirements in conditions enabling the security of their systems and/or data
 * to be ensured and, more generally, to use and operate it in the same conditions as regards security. The fact that
 * you are presently reading this means that you have had knowledge of the CeCILL license and that you accept its terms.
 *
 * @par COMMERCIAL SOFTWARE LICENCING
 * You can obtain this software from the author under other licencing terms for commercial purposes. For this you will need to
 * negotiate a specific contract with the author.
 */

#ifndef handy_string_convert_hpp_INCLUDED
#define handy_string_convert_hpp_INCLUDED

#include <boost/lexical_cast.hpp>
#include <boost/type_index.hpp>
#include <boost/algorithm/string.hpp>
#include <cctype>
#include <string>
#include <stdexcept>


namespace handy
{

template <typename T>
std::runtime_error make_string_convert_exception(const std::string& valueStr)
{
	return std::runtime_error("'" + valueStr + "' cannot be parsed as " + boost::typeindex::type_id<T>().pretty_name());
}

template <typename T>
T string_convert(const std::string& valueStr)
{
	try
	{
		return boost::lexical_cast<T>(valueStr);
	}
	catch (const boost::bad_lexical_cast& e)
	{
		throw make_string_convert_exception<T>(valueStr);
	}
}

/*
 * Declaration of template specializations
 */
template<> bool string_convert<bool>(const std::string& valueStr);
template<> int string_convert<int>(const std::string& valueStr);
template<> long string_convert<long>(const std::string& valueStr);
template<> long long string_convert<long long>(const std::string& valueStr);
template<> unsigned string_convert<unsigned>(const std::string& valueStr);
template<> unsigned long string_convert<unsigned long>(const std::string& valueStr);
template<> unsigned long long string_convert<unsigned long long>(const std::string& valueStr);
template<> float string_convert<float>(const std::string& valueStr);
template<> double string_convert<double>(const std::string& valueStr);
template<> long double string_convert<long double>(const std::string& valueStr);
template<> const std::string& string_convert<const std::string&>(const std::string& valueStr);
template<> const char* string_convert<const char*>(const std::string& valueStr);

} /* namespace handy */

#endif /* handy_string_convert_hpp_INCLUDED */

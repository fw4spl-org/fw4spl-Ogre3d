/* ***** BEGIN LICENSE BLOCK *****
 * FW4SPL - Copyright (C) IRCAD, 2014-2016.
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#ifndef __FWRENDEROGRE_FACTORY_NEW_HPP__
#define __FWRENDEROGRE_FACTORY_NEW_HPP__

#include <string>

#include <boost/make_shared.hpp>

#include <fwTools/macros.hpp>

#include "fwRenderOgre/config.hpp"
#include "fwRenderOgre/registry/detail.hpp"

namespace fwRenderOgre
{

class IRenderWindowInteractorManager;

namespace factory
{

template<class CLASSNAME > SPTR( CLASSNAME )  New();

/**
 * @brief Key class used to restrict access to Object construction.
 * See http://www.drdobbs.com/184402053
 * @class zizi
 */
class Key
{
template<typename CLASSNAME>
friend SPTR( CLASSNAME ) fwRenderOgre::factory::New();

Key()
{
}
};


FWRENDEROGRE_API SPTR( ::fwRenderOgre::IRenderWindowInteractorManager ) New(
    const ::fwRenderOgre::registry::KeyType & classname );


template<class CLASSNAME > SPTR( CLASSNAME )  New()
{
    SPTR(CLASSNAME) obj = std::make_shared< CLASSNAME >( Key() );
    return obj;
}

} // namespace factory

namespace interactorFactory
{

template<class CLASSNAME > SPTR( CLASSNAME )  New();

FWRENDEROGRE_API SPTR( ::fwRenderOgre::interactor::IInteractor ) New(
    const ::fwRenderOgre::registry::KeyType & classname );

template<class CLASSNAME > SPTR( CLASSNAME )  New()
{
    SPTR(CLASSNAME) obj = std::make_shared< CLASSNAME >( );
    return obj;
}

} // namespace interactorFactory

} // namespace fwRenderOgre

#endif /* __FWRENDEROGRE_FACTORY_NEW_HPP__ */



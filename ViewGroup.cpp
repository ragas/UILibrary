#include "ViewGroup.hpp"

View::Measure ViewGroup::calcChildMeasureSpec(View::Measure spec, int padding, LayoutParams::DimenType lpparam){
  View::Measure result;

  //If I am forced to be exact
  if(spec.spec == View::Measure::EXACT){
    //If child want to be Exact
    if (lpparam.param == LayoutParams::Params::EXACT){
      //Ok we allow child to be of that size
      result.spec = View::Measure::EXACT;
      result.value = lpparam.value;
    }else
      //If child want to match me
      if (lpparam.param == LayoutParams::Params::MATCH_PARENT){
	//Ok we tell it  my size
	result.spec = View::Measure::EXACT;
	result.value = spec.value;
      }else
	//If child want to determine its own size
	if (lpparam.param == LayoutParams::Params::WRAP_CONTENT){
	  //Ok, but don't be more than me.
	  result.spec = View::Measure::MAX;
	  result.value = spec.value;
	}

  }else if (spec.spec == View::Measure::MAX){ //If I have a max dimen to satisfy
    //If child want to be Exact
    if (lpparam.param == LayoutParams::Params::EXACT){
      //Ok we allow child to be of that size
      result.spec = View::Measure::EXACT;
      result.value = lpparam.value;
    }else
      //If child want to match me
      if (lpparam.param == LayoutParams::Params::MATCH_PARENT){
	//Ok we tell it  my size, but my size is not known so
	// we tell it to be max upto my size
	result.spec = View::Measure::MAX;
	result.value = spec.value;
      }else
	//If child want to determine its own size
	if (lpparam.param == LayoutParams::Params::WRAP_CONTENT){
	  //Ok, but don't be more than me.
	  result.spec = View::Measure::MAX;
	  result.value = spec.value;
	}
  }else if (spec.spec == View::Measure::ANY){ //If I can be any size
    //If child want to be Exact
    if (lpparam.param == LayoutParams::Params::EXACT){
      //Ok we allow child to be of that size
      result.spec = View::Measure::EXACT;
      result.value = lpparam.value;
    }else
      //If child want to match me
      if (lpparam.param == LayoutParams::Params::MATCH_PARENT){
	//Child want to match my size, lets find out how big it wants to be
	result.spec = View::Measure::ANY;
	result.value = 0;
      }else
	//If child want to determine its own size
	if (lpparam.param == LayoutParams::Params::WRAP_CONTENT){
	  //Child want to determine its own size.. lets find out how big
	  result.spec = View::Measure::ANY;
	  result.value = 0;
	}
  }

  return result;
}

void ViewGroup::measureChild(View* v, View::Measure wm, View::Measure hm){
  auto lp = v->getLayoutParams();
  //Compute the measuring spec for each child
  Measure new_wm = calcChildMeasureSpec(wm, mLeftPad + mRightPad, lp->width);
  Measure new_hm = calcChildMeasureSpec(hm, mTopPad + mBottomPad, lp->height);
  v->doMeasure(new_wm, new_hm);
}

void ViewGroup::measureChildren(View::Measure wm, View::Measure hm){
  for(auto& child : children){
    measureChild(child.get(), wm, hm);
  }
}


void ViewGroup::addView(ViewPtr v){
  if(v.get() == nullptr)
    return;
  addView(v, -1);
};

void ViewGroup::addView(ViewPtr v, int pos){
  if(v.get() == nullptr)
    return;

  std::unique_ptr<LayoutParams>& ulp = v->layoutParams;
  if(ulp.get() == nullptr)
    ulp = generateDefaultLayoutParams();
  addView(v, pos, std::move(ulp));
}

void ViewGroup::addView(ViewPtr v, int pos, std::unique_ptr<LayoutParams> lp){
  if(v.get() == nullptr)
    return;
  addChild(v,pos,std::move(lp));
}

void ViewGroup::addChild(ViewPtr v, int pos, std::unique_ptr<LayoutParams> p){
  v->setLayoutParams(std::move(p));
  v->parent = this;
  if(pos < 0){
    children.insert(children.end(),v);
  }else{
    children.insert(children.begin()+pos, v);
  }

}

void ViewGroup::delView(ViewPtr ){

}

void ViewGroup::drawChildren(Canvas& c){
  //Draws children in sequence
  for(auto& child : children){
    c.save();
    child->draw(c);
    c.restore();
  }

}

void ViewGroup::childFocused(View* child, View* focused){
  /**
     Set the child which contains the focused view
     Also unfocuses the old view if this is new child
   */
  if(focusedChild != nullptr)
    if(focusedChild != child)
      focusedChild->unfocus();
  focusedChild = child;

  if(parent != nullptr){
    parent->childFocused(this,focused);
  }
}

bool ViewGroup::requestFocus(FocusDirection dir){
  /**
     If a view wants focus, it always does it via its parent which is a ViewGroup
     This makes correct focust transfer from one view to other view
   */
  for(auto& child : children)
    if(child->requestFocus(dir))
      return true;

  return View::requestFocus(dir);
}


bool ViewGroup::dispatchMouseEvent(MouseEvent* ev){
  int orig_x = ev->x;
  int orig_y = ev->y;
  int x = ev->x + scrollX;
  int y = ev->y + scrollY;
  auto&& eventType = ev->getEventType();

  /**
     If this is mouse pressed then find the target
   */
  if(eventType == MousePressed::type){
    if(targetChild != nullptr)
      targetChild = nullptr;
    auto end = children.rend();
    
    for(auto childr = children.rbegin(); childr != end; childr++){
      auto& child = *childr;
      if (x > child->left && x < child->right &&
	  y > child->top && y < child->bottom){
	ev->x = x - child->left;
	ev->y = y - child->top;
	if(child->dispatchMouseEvent(ev)){
	  targetChild = child.get();
	  return true;
	}
      }
    }
  }

  /**
     If no child can take mouse event this view will handle it
   */
  if(targetChild == nullptr){
    ev->x = orig_x;
    ev->y = orig_y;
    return View::dispatchMouseEvent(ev);
  }

  /**
     If some child can take mouse event then let it handle and reset the
     target
   */
  auto tmpTarget = targetChild;
  if (eventType == MouseReleased::type){
    targetChild = nullptr;
  }

  ev->x = x - tmpTarget->left;
  ev->y = y - tmpTarget->top;

  return tmpTarget->dispatchMouseEvent(ev);
}

bool ViewGroup::dispatchTextEnteredEvent(TextEvent* tevent){
  if(focused)
    return  View::dispatchTextEnteredEvent(tevent);
  if (focusedChild !=nullptr)
    return focusedChild->dispatchTextEnteredEvent(tevent);
  return false;
}

bool ViewGroup::dispatchKeyEvent(KeyEvent* event){
  if(focused)
    return View::dispatchKeyEvent(event);
  if(onKeyEventListener != nullptr)
    if(onKeyEventListener(this, event))
      return true;
  if(focusedChild != nullptr)
    return focusedChild->dispatchKeyEvent(event);
  return false;
}

void ViewGroup::unfocus(){
  if(focusedChild !=nullptr)
    focusedChild->unfocus();
  focusedChild = nullptr;
}

void ViewGroup::childUnFocused(View* view, FocusDirection dir){
  auto end = children.end();
  auto it = children.begin();
  for(; it != end; ++it){
    if(view->id == (*it)->id){
      break;
    }
  }

  if(dir == FocusDirection::DOWN){
    if(it != end)
      ++it;
    if(it == end)
      it = children.begin();
  }else if (dir == FocusDirection::UP){
    if(it > children.begin())
      --it;
    else
      it = end-1;
  }
  (*it)->requestFocus();
}

void ViewGroup::interceptOnKey(std::function<bool(View*, KeyEvent*)> func){
  onKeyEventListener = func;
}

//
// Created by c on 05/07/2018 01:26 PM
//

#ifndef TOYS_FINITE_STATE_MACHINE_HH
#define TOYS_FINITE_STATE_MACHINE_HH

/* include section */

#include <type_traits>

#include "toys/types.hh"

/* class & function section */

namespace toys {

/*
 * static event & context class
 */
struct StaticEvent {};
struct StaticContext {};

/*
 * static state class
 * usage, define the derived class like:
 * =====================================
 * struct DerivedState : public StaticState<DerivedState, StateID> {
 *   static constexpr auto state_id = StateID::xx;
 * };
 * =====================================
 */
template<class Derived, class StateID>
struct StaticState {
	/*
	 * define StateID here for each derived class
	 * ID must be a enum type
	 */
	static_assert(std::is_enum<StateID>::value, "type param StateID must be a enum type");
	static constexpr StateID state_id = StateID();

	// constructor & destructor
	StaticState() {
		static_assert(std::is_base_of<StaticState, Derived>::value,
				"custom state must be derived from StaticState.");
	}

	// implement
	void enter() {}
	void leave() {}

	// interface
	void interface_enter() { static_cast<Derived*>(this)->enter(); }
	void interface_leave() { static_cast<Derived*>(this)->leave(); }
};


/*
 * static finite state machine
 * usage, define the derived class like:
 * =====================================
 * struct DerivedFSM : public StaticFSM<Derived, StateID> {
 *   using transition = transition_list<
 *     transition_rule<Event, S0, S1>,
 *     transition_rule<Event, S1, S2>,
 *   >;
 * };
 * =====================================
 * Event event;
 * DerivedFSM fsm;
 * fsm.set_state(StateID::XX);
 * fsm.trigger(event);
 * =====================================
 */
template<class Derived, class StateID>
struct StaticFSM {
	using type = Derived;
	using state_id_t = StateID;
	state_id_t current_state_id;

	// constructor & destructor
	StaticFSM() : current_state_id(state_id_t()) {
		static_assert(std::is_base_of<StaticFSM, Derived>::value,
				"custom finite state machine must be derived from StaticFSM.");
	}

	// get & set state
	void set_state(StateID const& s) { current_state_id = s; }
	StateID get_state() const { return current_state_id; }

	/*
	 * transition rule
	 */
	//template<class Event, class StateFrom, class StateTo>
	template<class StateFrom, class Event, class StateTo>
	struct transition_rule {
		using state_id_t = StateID;
		using event_t = Event;
		static constexpr auto state_from = StateFrom::state_id;
		static constexpr auto state_to = StateTo::state_id;

		static StateID trigger(Derived& fsm, event_t const& event) {
			Singleton<StateFrom>::instance().leave();
			Singleton<StateTo>::instance().enter();
			return state_to;
		}
	};

	/*
	 * transition_list type
	 */
	template<class... Rules>
	using transition_list = type_list<Rules...>;

	/*
	 * event rules template, extract event related rules from the whole transition list
	 */
	template<class Event, class...> struct event_rules;

	template<class Event, class... Rules>
	struct event_rules<Event, type_list<Rules...>> {
		template<class T>
		using event_condition_t = std::is_same<Event, typename T::event_t>;

		using type = typename type_filter<event_condition_t, Rules...>::type;
	};

	template<class Event>
	struct event_rules<Event, type_list<>> { using type = type_list<>; };

	template<class Event>
	StateID no_transition(Event const& event) { return current_state_id; }

	/*
	 * trigger with event rules
	 */
	template<class Event, class...> struct event_rules_trigger;

	template<class Event, class R, class... Rest>
	struct event_rules_trigger<Event, type_list<R, Rest...>> {
		static StateID trigger(Derived& self, Event const& event) {
			return self.current_state_id == R::state_from ?
				R::trigger(self, event) :
				event_rules_trigger<Event, type_list<Rest...>>::trigger(self, event);
		}
	};

	template<class Event>
	struct event_rules_trigger<Event, type_list<>> {
		static StateID trigger(Derived& self, Event const& event) {
			return self.no_transition(event);
		}
	};

	/*
	 * main interface, trigger method
	 */
	template<class Event>
	void trigger(Event && event) {
		using E = typename std::remove_reference<Event>::type;
		using rules = typename event_rules<E, typename Derived::transition>::type;
		auto self = static_cast<Derived&>(*this);
		current_state_id = event_rules_trigger<E, rules>::trigger(self, event);
	}
};

} // namespace toys

#endif//



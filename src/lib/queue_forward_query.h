/**
 *	queue_forward_query.h
 *
 *	@author	Masanori Yoshimoto <masanori.yoshimoto@gree.net>
 *
 *	$Id$
 */
#ifndef	QUEUE_FORWARD_QUERY_H
#define	QUEUE_FORWARD_QUERY_H

#include <string.h>

#include <boost/shared_ptr.hpp>

#include "storage.h"
#include "thread_queue.h"
#include "op.h"
#include "op_proxy_write.h"

using namespace std;

namespace gree {
namespace flare {

typedef class queue_forward_query queue_forward_query;
typedef boost::shared_ptr<queue_forward_query> shared_queue_forward_query;

/**
 *	forwarding query queue class
 */
class queue_forward_query : public thread_queue {
protected:
	storage::entry					_entry;
	string									_op_ident;
	op::result							_result;
	string									_result_message;

public:
	static const int max_retry = 4;

	queue_forward_query(storage::entry entry, string op_indent);
	virtual ~queue_forward_query();

	virtual int run(shared_connection c);
	op::result get_result() { return this->_result; };
	string get_result_message() { return this->_result_message; };
	string get_op_ident() { return this->_op_ident; };
	storage::entry& get_entry() { return this->_entry; };

protected:
	op_proxy_write* _get_op(string op_ident, shared_connection c);
};

}	// namespace flare
}	// namespace gree

#endif	// QUEUE_FORWARD_QUERY_H
// vim: foldmethod=marker tabstop=2 shiftwidth=2 autoindent

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgresse <bgresse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 19:34:06 by zrebhi            #+#    #+#             */
/*   Updated: 2023/10/09 10:57:28 by bgresse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

Channel::Channel() {}

Channel::Channel(const std::string &channelName) : _name(channelName) {}

Channel::~Channel() {}

void Channel::addUser(const Client &user) {
	this->_users.insert(std::make_pair(user.getSocket(), user));
	std::cout << this->_users[user.getSocket()].getNickname() << " added to " << this->_name << std::endl;
}

void Channel::kickUser(int socket) {
    std::map<int, Client>::iterator it = _users.find(socket);

    if (it != _users.end()) {
        std::cout << "Kicking user: " << it->second.getNickname() << " from " << _name << std::endl;
        _users.erase(it);
    } else {
        std::cout << "User with socket " << socket << " not found in " << _name << std::endl;
    }
}

void Channel::printUserList() {
	std::map<int, Client>::iterator it = this->_users.begin();

	for (; it != this->_users.end(); it++)
		std::cout << it->second.getNickname() << std::endl;
}

std::string Channel::getName() const {
	return this->_name;
}

std::map<int, Client> Channel::getUserList() const {
	return this->_users;
}
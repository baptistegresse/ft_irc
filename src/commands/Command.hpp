/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgresse <bgresse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 18:50:31 by zrebhi            #+#    #+#             */
/*   Updated: 2023/10/05 22:13:24 by bgresse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <vector>
#include "../client/Client.hpp"
#include "../channels/Channel.hpp"
#include "../server/Server.hpp"

class Client;
class Channel;
class Server;

class Command {
public:
	Command(const std::vector<std::string> &commandArray, Client &client);
	~Command();

	void	user();
	void	nick();
	void	join(std::map<std::string, Channel> &channels);
	void	list(std::map <std::string, Channel> &channels);
	void	privmsg(Server ircServ, Client user);
	void	kick(std::map<std::string, Channel> &channels, Client user);

private:
	std::vector<std::string> _commandArray;
	Client&	_client;

	void	channelMessage(Server ircServ, Client user);
	bool	checkChannelExists(Server ircServ, Client user);
	bool	checkIsChannelMember(Server ircServ, Client user);
	void	privateMessage(Server ircServ, Client user);
};
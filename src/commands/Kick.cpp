/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgresse <bgresse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 22:11:18 by bgresse           #+#    #+#             */
/*   Updated: 2023/10/09 12:32:39 by bgresse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

Client findClient(std::string name, const std::map<std::string, Channel> &channels)
{
    for (std::map<std::string, Channel>::const_iterator it = channels.begin(); it != channels.end(); ++it)
    {
        const std::map<int, Client> &users = it->second.getUserList();

        for (std::map<int, Client>::const_iterator userIt = users.begin(); userIt != users.end(); ++userIt)
        {
            if (userIt->second.getNickname() == name)
                return userIt->second;
        }
    }
    return Client();
}

void Command::kick(std::map<std::string, Channel> &channels, Client user)
{
    if (this->_commandArray.size() < 4)
    {
        ft_send(user, ":461 " + user.getNickname() + " :Not enough parameters");
        return;
    }

    std::string channel = this->_commandArray[1];
    channel = channel.substr(1);
    std::string targetName =  this->_commandArray[2];
    std::string comment = this->_commandArray[3];

    Client targetClient = findClient(targetName, channels);

    if (targetClient.getSocket() == -1)
    {
        ft_send(user, ":441 " + user.getNickname() + " " + targetName + " :User not found");
        return;
    }

    std::map<std::string, Channel>::iterator it = channels.find(channel);
    if (it != channels.end())
    {
        it->second.kickUser(targetClient.getSocket());
        ft_send(targetClient, ":" + user.getNickname() + " KICK " + channel + " " + targetName + " :" + comment);
    } if (this->_commandArray.size() < 4)
    {
        ft_send(user, ":461 " + user.getNickname() + " :Not enough parameters");
        return;
    }
    else
    {
        ft_send(user, ":403 " + user.getNickname() + " " + channel + " :No such channel");
        return;
    }
}

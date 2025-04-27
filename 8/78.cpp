#include <iostream>
#include <vector>
#include <string>
#include <ctime>

class Permission {
public:
    std::string name;
    std::string description;

    Permission(const std::string& name, const std::string& description)
        : name(name), description(description) {
    }
};

class Role {
public:
    std::string name;
    std::vector<Permission> permissions;

    Role(const std::string& name) : name(name) {}

    void addPermission(const Permission& permission) {
        permissions.push_back(permission);
    }

    bool hasPermission(const std::string& permissionName) const {
        for (const auto& perm : permissions) {
            if (perm.name == permissionName) {
                return true;
            }
        }
        return false;
    }
};

class User {
public:
    std::string username;
    std::string email;
    Role* role;
    std::vector<std::string> notifications;

    User(const std::string& username, const std::string& email, Role* role = nullptr)
        : username(username), email(email), role(role) {
    }

    void assignRole(Role* newRole) {
        role = newRole;
    }

    bool can(const std::string& permissionName) const {
        return role && role->hasPermission(permissionName);
    }

    void notify(const std::string& message) {
        notifications.push_back(message);
    }
};

class Project;

class Comment {
public:
    std::string text;
    User* author;
    std::time_t createdAt;

    Comment(const std::string& text, User* author)
        : text(text), author(author) {
        createdAt = std::time(nullptr);
    }
};

class Task {
public:
    std::string title;
    std::string description;
    Project* project;
    User* creator;
    User* assignee;
    std::vector<Comment> comments;
    std::string status;

    Task(const std::string& title, const std::string& description, Project* project, User* creator, User* assignee = nullptr)
        : title(title), description(description), project(project), creator(creator), assignee(assignee), status("Open") {
    }

    void addComment(const Comment& comment) {
        comments.push_back(comment);

        if (assignee) {
            assignee->notify("New comment in task '" + title + "': " + comment.text);
        }
        creator->notify("New comment in task '" + title + "': " + comment.text);
    }
};

class Project {
public:
    std::string name;
    std::string description;
    User* creator;
    std::vector<Task> tasks;
    std::vector<Comment> comments;
    std::vector<User*> members;

    Project(const std::string& name, const std::string& description, User* creator)
        : name(name), description(description), creator(creator) {
        members.push_back(creator);
    }

    void addMember(User* user) {
        members.push_back(user);
    }

    void addTask(const Task& task) {
        tasks.push_back(task);
    }

    void addComment(const Comment& comment) {
        comments.push_back(comment);
        for (auto member : members) {
            member->notify("New comment in project '" + name + "': " + comment.text);
        }
    }
};
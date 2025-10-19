#include "multiplechoiceknapsacksolver/instance_builder.hpp"

using namespace multiplechoiceknapsacksolver;

void InstanceBuilder::add_item(
        GroupId group_id,
        Profit profit,
        Weight weight)
{
    ItemId item_id = instance_.items_.size();
    Item item;
    item.group_id = group_id;
    item.profit = profit;
    item.weight = weight;
    instance_.items_.push_back(item);
    while ((GroupId)instance_.groups_.size() <= group_id)
        instance_.groups_.push_back(Group());
    instance_.groups_[group_id].item_ids.push_back(item_id);
}

void InstanceBuilder::read(
        const std::string& instance_path,
        const std::string& format)
{
    std::ifstream file(instance_path);
    if (!file.good()) {
        throw std::runtime_error(
                "Unable to open file \"" + instance_path + "\".");
    }

    if (format == "standard" || format == "") {
        read_standard(file);
    } else {
        throw std::invalid_argument(
                "Unknown instance format \"" + format + "\".");
    }

    file.close();
}

void InstanceBuilder::read_standard(std::ifstream& file)
{
    GroupId number_of_groups;
    Profit profit;
    Weight weight;
    ItemId group_number_of_items;

    file >> number_of_groups >> weight;
    set_capacity(weight);
    for (GroupId group_id = 0; group_id < number_of_groups; ++group_id) {
        file >> group_number_of_items;
        for (ItemId item_id = 0;
                item_id < group_number_of_items;
                ++item_id) {
            file >> profit >> weight;
            add_item(group_id, profit, weight);
        }
    }
}

Instance InstanceBuilder::build()
{
    this->instance_.bound_ = 0;
    for (GroupId group_id = 0;
            group_id < this->instance_.number_of_groups();
            ++group_id) {
        Group& group = this->instance_.groups_[group_id];
        for (ItemId item_id: group.item_ids) {
            const Item& item = this->instance_.item(item_id);
            group.highest_profit = (std::max)(
                    group.highest_profit,
                    item.profit);
        }
        this->instance_.bound_ += group.highest_profit;
    }
    return std::move(instance_);
}

#include<bits/stdc++.h>
using namespace std;

int main()
{
    int n,q;
    cin>>n>>q;
    string curr="",attr_name;
    map<string,string>m;
    cin.ignore(); // to remove nextline character 

    // for every word in HTML line check:
    for(int i=0;i<n;i++)
    {
        string line,tag,extract;
        getline(cin,line);
        stringstream ss(line);

        // process the html lines
        while(getline(ss,extract,' '))
        {
             //if it's a tag
             if(extract[0]=='<')
             {
                 // if it's an opening tag
                 if(extract[1]!='/')
                 {
                     // remove the opening bracket
                     tag=extract.substr(1);
                     // for tags without attributes
                     // <a>
                     if(tag[tag.length()-1]=='>')
                     {
                         tag.pop_back();
                     }

                     // check if nesting is needed
                     if(curr.size()>0)
                     {
                         // nest this tag
                         curr+="." + tag; // tag1.tag2
                     }
                     else
                     {
                         curr=tag;
                     }
                 }
                 // if it's an closing tag
                 else
                 {
                     tag=extract.substr(2, (extract.find('>')-2));

                     // check if a nested tag has to be closed

                     // if curr=="tag1.tag2"

                        size_t pos=curr.find("." + tag);
                        if(pos!=string::npos)
                        {
                            // remove the nested tag
                            curr=curr.substr(0,pos);
                        }
                        else
                        {
                            // all tags are closed
                            curr="";
                        }

                 }
             }
            // if it's an attribute's value
            else if(extract[0]=='"')
            {
                // caputre the value
                size_t pos =extract.find_last_of('"');
                string attr_value=extract.substr(1,pos-1);
                // addd to the map
                m[attr_name]=attr_value;
            }

            else
            {
                if(extract!="=")
                {
                    // it's definitely an attribute name
                    attr_name=curr + "~" + extract;
                }
            }
        }
    }
    string query;
    for(int i=0;i<q;i++)
    {
        getline(cin,query);

        // search the map
        map<string,string>::iterator itr=m.find(query);
        if(itr!=m.end())
        {
            cout<<itr->second<<endl;
        }
        else
        {
            cout<<"Not found!"<<endl;
        }
    }

    return 0;
}
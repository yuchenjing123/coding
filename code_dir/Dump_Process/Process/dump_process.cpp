
#include "dump_process.h"

DumpProcess::DumpProcess()
{
    m_response = new RESPONSE;
    m_response->type = TYPE::DUMP;
    m_response->result = RESULT::INVALID_PROCESS;
    m_response->pDumpMap = new map<DUMP_TYPE, VALUE *>;
}
DumpProcess::~DumpProcess()
{
}

bool DumpProcess::ishave_title(string filename)
{
	string::size_type position;
    if (( position= filename.find(';')) !=  filename.npos)
    {
        return true;
    }
    else
    {
        return false;
    }
}

DUMP_FILE_NAME DumpProcess::file_type(string filename)
{
    DUMP_FILE_NAME Temp = INVILAD_NAME;
	string::size_type position;
	
    if (  (position=filename.find("frame"))   != filename.npos)
    {
        Temp = FRAME;
		cout<< Temp  << endl;
        return Temp;
    }
    else if ((filename.find("gyro")) !=  filename.npos)
    {
        Temp = GYRO;
        return Temp;
    }
    else if ((filename.find("ois")) != filename.npos)
    {
        Temp = OIS;
        return Temp;
    }
    else
    {
        return Temp;
    }
}

RESPONSE* DumpProcess::process(string& filename)
{
    char filenamestr[50] = {0};
	filenamestr[0] = '.';
	filenamestr[1] = '/';
    int  a = filename.length();
    for(int t = 0; t<a ; t++ )
    {
         filenamestr[t+2] = filename[t];
    }

    FILE *fp = NULL;
    char *line;
    char *tok;
    char buffer[8192] = {0};
    if ((fp = fopen(filenamestr, "at+")) != NULL)
    {
        //判断有无分号
        string tempfile = filename;
        bool is_title = ishave_title(tempfile);

        //判断文件是哪种类型
        DUMP_FILE_NAME FileType = INVILAD_NAME;
        if ((FileType = file_type(tempfile)) == FRAME)
        {
            line = fgets(buffer, sizeof(buffer), fp);

            tok = strtok(line, ";");
            int i = 0;
            tok = strtok(tok, ",");
            while (tok != NULL)
            {
                i++;
                tok = strtok(NULL, ",");
            }
            for (int j = 0; j < i; j++)
            {
                ((*(m_response->pDumpMap))[(DUMP_TYPE)j])= new VALUE;
            }
            while ((line = fgets(buffer, sizeof(buffer), fp)) != NULL)
            {
                CSVLINE Line;
                line = strtok(line, ",");
                int lineCount = 0;
                while (line != NULL)
                {
                    float a = atof(line);
                    Line.row_list.push_back(a);
                    if (lineCount == 6)
                    {
                        Line.time = a;
                    }
                    lineCount++;
                    line = strtok(NULL, ",");
                }
                m_list.push_back(Line);
            }
        }
        if ((FileType = file_type(tempfile)) == GYRO)
        {
            for (int j = 0; j < 5; j++)
            {
                ((*(m_response->pDumpMap))[(DUMP_TYPE)j]) = new VALUE;
            }
            while ((line = fgets(buffer, sizeof(buffer), fp)) != NULL)
            {
                CSVLINE Line;
                line = strtok(line, ",");
                int lineCount = 0;
                while (line != NULL)
                {
                    if (lineCount == 5)
                    {
                        break;
                    }
                    float a = atof(line);
                    Line.row_list.push_back(a);
                    if (lineCount == 1)
                    {
                        Line.time = a;
                    }
                    lineCount++;
                    line = strtok(NULL, ",");
                }
                m_list.push_back(Line);
            }
        }
        if ((FileType = file_type(tempfile)) == OIS)
        {
            for (int j = 0; j < 4; j++)
            {
                 ((*(m_response->pDumpMap))[(DUMP_TYPE)j])= new VALUE;
            }
            while ((line = fgets(buffer, sizeof(buffer), fp)) != NULL)
            {
                CSVLINE Line;
                line = strtok(line, ",");
                int lineCount = 0;
                while (line != NULL)
                {
                    if (lineCount == 4)
                    {
                        break;
                    }
                    float a = atof(line);
                    Line.row_list.push_back(a);
                    if (lineCount == 1)
                    {
                        Line.time = a;
                    }
                    lineCount++;
                    line = strtok(NULL, ",");
                }
                m_list.push_back(Line);
            }
        }
        //order by time
        m_list.sort();

        //insert value after order from list to map
        list<CSVLINE>::iterator iter; //各行元素的迭代器
        list<float>::iterator iter2;  //每行元素的迭代器
        map<DUMP_TYPE, VALUE *>::iterator iter3;
        //map的迭代器
        iter = m_list.begin();
        int colnum = 0;
        while (iter != m_list.end())
        {
            colnum = 0;
            iter2 = (*iter).row_list.begin();
            while (iter2 != (*iter).row_list.end())
            {
                ((*(m_response->pDumpMap))[(DUMP_TYPE)colnum])->col_list.push_back((*iter2));
                colnum++;
                iter2++;
            }
            iter++;
        }
        // map<DUMP_TYPE,VALUE*>::iterator ite;     //map迭代器
        // list<float>::iterator ite_list;		//list迭代器
        // ite=(*(m_response->list)).begin();
        // 		int mark =0;
        // 		while(ite != (*(m_response->list)).end())
        // 		{
        // 			//输出first，代表map的key值，对应的是csv文件的列属性，属性的意义在DUMP_TYPE枚举中列出
        // 			cout<< ite->first <<endl;
        // 			ite_list = (*(m_response->list))[mark]->list.begin();
        // 			while(ite_list!=(*(m_response->list))[mark]->list.end())
        // 			{
        // 					cout << *ite_list<<"	"; //输出每个列中对应的值，渲染的小伙伴要读取这部分数据
        // 					ite_list++;
        // 			}
        // 			mark++;
        // 			ite++;
        // 		}
        fclose(fp);
        fp = NULL;
        m_response->result = RESULT::SUCCESS;
        //如果是frame类型文件应计算zoom
        if(FileType  == FRAME)
        {
             ((*(m_response->pDumpMap))[ife_zoom]) = new VALUE;
            ((*(m_response->pDumpMap))[ipe_zoom]) = new VALUE;
            ((*(m_response->pDumpMap))[total_zoom]) = new VALUE;
            //计算zoom
            float maxValueIFE =0;
            float maxValueIPE =0;
            //计算eis_pre_crop_vOUT_windowWidth中的最大值
            //(((*(m_response->pDumpMap))[eis_pre_crop_vOUT_windowWidth])->col_list.begin())
            //(((*(m_response->pDumpMap))[eis_pre_crop_vOUT_windowWidth])->col_list.end())
            auto max = max_element((((*(m_response->pDumpMap))[eis_pre_crop_vOUT_windowWidth])->col_list.begin()),(((*(m_response->pDumpMap))[eis_pre_crop_vOUT_windowWidth])->col_list.end()));
            maxValueIFE = *max;
            //计算output_crop_fov_windowWidth中的最大值
           //(((*(m_response->pDumpMap))[output_crop_fov_windowWidth])->col_list.begin())
           //(((*(m_response->pDumpMap))[output_crop_fov_windowWidth])->col_list.end())
            max = max_element((((*(m_response->pDumpMap))[output_crop_fov_windowWidth])->col_list.begin()),(((*(m_response->pDumpMap))[output_crop_fov_windowWidth])->col_list.end()));
            maxValueIPE = *max;
            //计算ifezoom
            list<float>::iterator iter4,iter_4;
            iter4 = ((*(m_response->pDumpMap))[ife_zoom])->col_list.begin();
            iter_4 = ((*(m_response->pDumpMap))[eis_pre_crop_vOUT_windowWidth])->col_list.begin();
            while(iter4 != ((*(m_response->pDumpMap))[ife_zoom])->col_list.end())
            {      
                    ((*(m_response->pDumpMap))[ife_zoom])->col_list.push_back((*iter_4)/maxValueIFE);
                    iter4++;
                    iter_4++;
            }
            //计算ipezoom
            list<float>::iterator iter5,iter_5;
            iter5 = ((*(m_response->pDumpMap))[ipe_zoom])->col_list.begin();
            iter_5 = ((*(m_response->pDumpMap))[output_crop_fov_windowWidth])->col_list.begin();
            while(iter5 != ((*(m_response->pDumpMap))[ipe_zoom])->col_list.end())
            {
                    ((*(m_response->pDumpMap))[ipe_zoom])->col_list.push_back((*iter_5)/maxValueIPE);
                    iter5++;
                    iter_5++;
            }
            iter4 = ((*(m_response->pDumpMap))[ife_zoom])->col_list.begin();
            iter5 = ((*(m_response->pDumpMap))[ipe_zoom])->col_list.begin();
            list<float>::iterator iter6;
            iter6 =  ((*(m_response->pDumpMap))[total_zoom])->col_list.begin();
            while(iter6 != ((*(m_response->pDumpMap))[total_zoom])->col_list.end())
            {
                    ((*(m_response->pDumpMap))[total_zoom])->col_list.push_back((*iter4)*(*iter5));
                    iter4++;
                    iter5++;
                    iter6++;
            }      
        }
        
    }
//测试map中是否写入正确的值
map<DUMP_TYPE,VALUE*>::iterator ite;     //map迭代器
list<float>::iterator ite_list;		//list迭代器
ite= (*(m_response->pDumpMap)).begin();
int mark =0;
while(ite !=  (*(m_response->pDumpMap)).end())
{
	//输出first，代表map的key值，对应的是csv文件的列属性，属性的意义在DUMP_TYPE枚举中列出
	cout<< ite->first <<endl;
	ite_list =  ((*(m_response->pDumpMap))[(DUMP_TYPE)mark])->col_list.begin();      
	while(ite_list!=((*(m_response->pDumpMap))[(DUMP_TYPE)mark])->col_list.end())
	{
		cout << *ite_list<<"	"; //输出每个列中对应的值，通信的小伙伴要读取这部分数据给渲染的小伙伴
		ite_list++;
	}
		mark++;
		ite++;
}

        //加入到任务队列中
        //加锁
        pthread_mutex_lock(&g_mutex);
        g_TaskQueue.push(m_response);
        //解锁
        pthread_mutex_unlock(&g_mutex);

}

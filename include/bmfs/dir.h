/* BareMetal File System Utility */
/* Written by Ian Seyler of Return Infinity */
/* v1.3.0 (2017 10 11) */

#ifndef BMFS_DIR_H
#define BMFS_DIR_H

#include "entry.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

struct BMFSDisk;

/** @defgroup dir-api Directory API
 * Directory traversal, entry addition
 * or deletion and sorting.
 */

/** A BMFS directory.
 * @ingroup dir-api
 */

struct BMFSDir
{
	/** The disk that contains the directory. */
	struct BMFSDisk *Disk;
	/** The entry containing the position and
	 * other information regarding the directory. */
	struct BMFSEntry Entry;
	/** The offset to the directory entry. This
	 * is used if an entry is added to this directory,
	 * and the directory size must be updated. */
	int64_t EntryOffset;
	/** The entry that was last read from the
	 * client. */
	struct BMFSEntry CurrentEntry;
	/** The index of the current entry that the
	 * next read operation will read. */
	uint64_t CurrentIndex;
};

/** Initializes a directory.
 * After calling this function, also
 * set the disk by calling @ref bmfs_dir_set_disk.
 * @param dir The directory to initialize.
 * @ingroup dir-api
 * */

void bmfs_dir_init(struct BMFSDir *dir);

/** Assigns the disk that will be used
 * for the directory operations.
 * @param dir An initialized directory structure.
 * @param disk The disk to assign the directory.
 * @ingroup dir-api
 * */

void bmfs_dir_set_disk(struct BMFSDir *dir,
                       struct BMFSDisk *disk);

/** Imports the directory from the disk.
 * The disk must be currently pointing to
 * the directory entry. If the entry is not
 * a directory, or the read operation fails,
 * then this function will fail. The directory
 * should already have a directory assigned to
 * it (if not, use @ref bmfs_dir_set_disk.)
 * @param dir An initialized directory structure.
 * @returns Zero on success, an error code on failure.
 * @ingroup dir-api
 * */

int bmfs_dir_import(struct BMFSDir *dir);

/** Moves to the next entry in the directory.
 * @param dir An initialized directory.
 * @returns The next entry in the directory.
 * If the end of the directory is reached, then
 * a null pointer is returned.
 * */

const struct BMFSEntry *bmfs_dir_next(struct BMFSDir *dir);

 #ifdef __cplusplus
} /* extern "C" { */
#endif

#endif /* BMFS_DIR_H */

